#include "Editor.h"
#include <iostream>
#include <MathDefines.h>
#include <Core/UserEntry/InputManager.h>
#include <Core/Profiler/Profiler.h>
#include "stb_image.h"
#include "opengl_helper.h"

void IsTriggered(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//Quantix::Core::UserEntry::InputMgr::GetInstance()->CheckKeys(key, action);
}

Editor::Editor(QXuint width, QXuint height) :
	_win{ width, height },
	_lib{"QuantixEngine"},
	_docker{},
	_folder{},
	_menuBar{},
	_hierarchy{},
	_play{ false },
	_pause{ false },
	_guizmoType{ ImGuizmo::OPERATION::TRANSLATE },
	_flagsEditor{}
{
	_cameraEditor = new Quantix::Core::Components::Camera({ 0, 7, -10 }, { 0, -1, 1 }, Math::QXvec3::up);
	_lib.load();
	if (!_lib.is_loaded())
		std::cout << _lib.get_error_string() << std::endl;

	//Init Callback
	glfwSetKeyCallback(_win.GetWindow(), IsTriggered);

	_mouseInput = new MouseTest({ false, 0.0f, 0.0f, GetMousePos().x, GetMousePos().y });

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF("media/Font/Roboto-Medium.otf", 20.0f);
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
   // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;           // Enable Docking

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(_win.GetWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 330");

	GLFWimage icon;
	icon.pixels = stbi_load("media/IconEditor/logo_6_1.png", &icon.width, &icon.height, 0, STBI_rgb_alpha);

	glfwSetWindowIcon(_win.GetWindow(), 1, &icon);

	_app = new Quantix::Core::Platform::Application(_win.GetWidth(), _win.GetHeight());

	_root = _app->scene->GetRoot();

	_simImg.insert(std::make_pair("Play", _app->manager.CreateTexture("media/IconEditor/Play.png")));
	_simImg.insert(std::make_pair("Pause", _app->manager.CreateTexture("media/IconEditor/Pause.png")));
	_simState.insert(std::make_pair("Play", false));
	_simState.insert(std::make_pair("Pause", false));
}

Editor::~Editor()
{
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	//unload lib rttr
	_lib.unload();

	delete _app;
}

void Editor::Init()
{
	InitImGui();

	_app->info.proj = { Math::QXmat4::CreateProjectionMatrix(_app->info.width, _app->info.height, 0.1f, 1000.f, 80.f) };

	ImGui::GetStyle().WindowRounding = 0.f;
	_flagsEditor = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoCollapse;
	ImGui::Begin("Quantix Editor", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove);

	DrawSimulation();

	_docker.Init();
	ImGui::DockSpace(_docker.GetIDDockspace(), ImVec2(0, 0), ImGuiDockNodeFlags_NoTabBar);

	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Editor::InitImGui()
{
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGuizmo::BeginFrame();

	// Disabling mouse for ImGui if mouse is captured by the app (it must be done here)
	if (_mouseInput->MouseCaptured)
		ImGui::GetIO().MousePos = ImVec2(-FLT_MAX, -FLT_MAX);
}

void Editor::Update(QXuint FBO)
{
	InitImGui();

	_fbo = FBO;
	static QXint i = 0;
	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::SetNextWindowViewport(viewport->ID);

	ImGui::PushStyleColor(ImGuiCol_MenuBarBg, ImVec4(1, 1, 1, 1));
	ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1, 1, 1, 1));
	ImGui::Begin("Editor", NULL, _flagsEditor);

	START_PROFILING("Editor");

	DrawMenuBar();
	DrawSimulation();
	ImGui::DockSpace(_docker.GetIDDockspace(), ImVec2(0, 0), ImGuiDockNodeFlags_NoTabBar);

	ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove;

	for (QXuint i{ 0 }; i < _docker.GetWindowsEditor().size(); i++)
		Draw(_docker.GetWindowsEditor()[i], flags);

	STOP_PROFILING("Editor");
	ImGui::End();

	ImGui::PopStyleColor();
	ImGui::PopStyleColor();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Editor::Draw(const QXstring& name, ImGuiWindowFlags flags)
{
	if (name == "Console")
		DrawConsole(name, flags);
	else if (name == "Explorer")
		DrawExplorer(name, flags);
	else if (name == "Scene")
		DrawScene(name, flags);
	else if (name == "Hierarchy")
		DrawHierarchy(name, flags);
	else if (name == "Shader")
		DrawShader(name, flags);
	else if (name == "Inspector")
		DrawInspector(name, flags);
}

void Editor::DrawMenuBar()
{
	static QXint i = 0;
	if (i == 0)
	{
		Quantix::Core::Debugger::Logger::GetInstance()->SetWarning("Menu bar not fully implemented.");
		i++;
	}
	_menuBar.Update(_app);
}

void Editor::DrawHierarchy(const QXstring& name, ImGuiWindowFlags flags)
{
	_hierarchy.Update(name, flags, _root->GetTransform(), _app->scene);
}

void Editor::DrawShader(const QXstring& name, ImGuiWindowFlags flags)
{
	ImGui::Begin(name.c_str(), NULL, flags);
	{
		if (_app->manager.GetShaders().size() > 0)
		{
			for (auto it = _app->manager.GetShaders().begin(); it != _app->manager.GetShaders().end(); ++it)
			{
				if (ImGui::TreeNode(it->first.c_str()))
				{
					InspectProgram(it->second->GetID());
					ImGui::TreePop();
				}
			}
		}
	}
	ImGui::End();
}

void Editor::Simulation()
{
	QXint pos = -20;
	for (auto it = _simState.rbegin(); it != _simState.rend(); ++it)
	{
		if (!it->second)
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1, 1, 1, 1));
		else
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(44 / 255, 62 / 255, 80 / 255, 1));
		ImGui::SetCursorPos(ImVec2(ImGui::GetWindowSize().x / 2 + pos, 0));
		if (ImGui::ImageButton((ImTextureID)_simImg[it->first]->GetId(), ImVec2(25, 25)))
			it->second = !it->second;
		ImGui::PopStyleColor();
		pos *= -1;
	}
}

void Editor::DrawSimulation()
{
	ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove;
	ImGui::BeginChild(ImGui::GetID("Editor"), ImVec2(0, 35), false, flags);
	Simulation();
	if (_simState["Play"])
	{
		if (!_simState["Pause"])
		{
			//Update Scene
			_play = true;
			if (!_activateFocus)
			{
				_mouseInput->MouseCaptured = true;
				glfwSetInputMode(_win.GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

				Math::QXvec2 mousePos = GetMousePos();
				_mouseInput->MouseX = mousePos.x;
				_mouseInput->MouseY = mousePos.y;

				_activateFocus = true;
			}
		}
		else
		{
			_pause = true;
			_activateFocus = false;
		}
	}
	else
	{
		_play = false;
		_pause = false;
		_simState["Pause"] = false;
		_activateFocus = false;
	}
	ImGui::EndChild();
}

void Editor::MoveObject(Quantix::Physic::Transform3D* transform, Math::QXmat4& matrix, Math::QXmat4& matrixTmp)
{
	Math::QXmat4 matrixTmp2 = Math::QXmat4::CreateTRSMatrix(transform->GetPosition(), Math::QXquaternion(1, 0, 0, 0), transform->GetScale());
	Math::QXvec3 translation, transTmp, rotation, rotTmp, scale, scaleTmp;

	if (_guizmoType == ImGuizmo::OPERATION::TRANSLATE)
	{
		ImGuizmo::Manipulate(_cameraEditor->GetLookAt().array, _app->info.proj.array, ImGuizmo::OPERATION::TRANSLATE, ImGuizmo::MODE::WORLD, matrix.array);
		ImGuizmo::DecomposeMatrixToComponents(matrixTmp.array, transTmp.e, rotation.e, scale.e);
		ImGuizmo::DecomposeMatrixToComponents(matrix.array, translation.e, rotation.e, scale.e);
		transform->Translate(translation - transTmp);
	}
	else if (_guizmoType == ImGuizmo::OPERATION::ROTATE)
	{
		ImGuizmo::Manipulate(_cameraEditor->GetLookAt().array, _app->info.proj.array, ImGuizmo::OPERATION::ROTATE, ImGuizmo::MODE::WORLD, matrixTmp2.array);
		
		ImGuizmo::DecomposeMatrixToComponents(matrixTmp2.array, translation.e, rotTmp.e, scale.e);
		rotTmp = rotTmp * (Q_PI / 180);

		transform->Rotate(Math::QXquaternion::EulerToQuaternion(rotTmp));
	}
	else
	{
		ImGuizmo::Manipulate(_cameraEditor->GetLookAt().array, _app->info.proj.array, ImGuizmo::OPERATION::SCALE, ImGuizmo::MODE::WORLD, matrix.array);
		ImGuizmo::DecomposeMatrixToComponents(matrixTmp.array, translation.e, rotation.e, scaleTmp.e);
		ImGuizmo::DecomposeMatrixToComponents(matrix.array, translation.e, rotation.e, scale.e);
		transform->Scale(scale - scaleTmp);
	}

	transform->SetTRS(matrix);
}

void Editor::ShowGuizmoObject(Quantix::Physic::Transform3D* transform)
{
	Math::QXmat4 matrix = transform->GetTRS();
	Math::QXmat4 matrixTmp = transform->GetTRS();
	ImVec2 size = ImGui::GetWindowSize();
	ImVec2 pos = ImGui::GetWindowPos();
	ImGuiIO& io = ImGui::GetIO();

	ImGuizmo::SetRect(pos.x, pos.y, size.x, size.y);
	pos.y += 25;
	ImGuizmo::DrawCube(_cameraEditor->GetLookAt().array, _app->info.proj.array, matrix.array);
	ImGuizmo::ViewManipulate(_cameraEditor->GetLookAt().array, 50.f, pos, ImVec2(128,128), 0x10101010);

	MoveObject(transform, matrix, matrixTmp);
}

void Editor::DrawGuizmo()
{
	if (GetKey(QX_KEY_SPACE) == Quantix::Core::UserEntry::EKeyState::PRESSED)
	{
		if (_guizmoType == ImGuizmo::OPERATION::TRANSLATE)
			_guizmoType = ImGuizmo::OPERATION::ROTATE;
		else if (_guizmoType == ImGuizmo::OPERATION::ROTATE)
			_guizmoType = ImGuizmo::OPERATION::SCALE;
		else if (_guizmoType == ImGuizmo::OPERATION::SCALE)
			_guizmoType = ImGuizmo::OPERATION::TRANSLATE;
	}

	if (_hierarchy.GetInspector() != nullptr)
		ShowGuizmoObject(_hierarchy.GetInspector()->GetTransform());
}

void Editor::DrawScene(const QXstring& name, ImGuiWindowFlags flags)
{
	static QXint i = 0;

	ImGui::Begin(name.c_str(), NULL, flags);
	{
		ImGuizmo::SetDrawlist();
		if (i == 0)
		{
			Quantix::Core::Debugger::Logger::GetInstance()->SetError("No Scene load.");
			i++;
		}
		if (ImGui::BeginPopupContextWindow("Context Menu", 1, false))
		{
			_mouseInput->MouseCaptured = true;
			glfwSetInputMode(_win.GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

			Math::QXvec2 mousePos = GetMousePos();
			_mouseInput->MouseX = mousePos.x;
			_mouseInput->MouseY = mousePos.y;

			ImGui::CloseCurrentPopup();
			ImGui::EndPopup();
		}
		ImVec2 size = ImGui::GetWindowSize();
		size.y -= 50;
		ImGui::Image((ImTextureID)(size_t)_fbo, size, { 0.f, 1.f }, { 1.f, 0.f });
		if (!_mouseInput->MouseCaptured)
			DrawGuizmo();
	}
	ImGui::End();
}

void Editor::PrintLog()
{
	ImGuiStyle& style = ImGui::GetStyle();
	for (QXuint i = 0; i < Quantix::Core::Debugger::Logger::GetInstance()->GetData().size(); i++)
	{
		if (Quantix::Core::Debugger::Logger::GetInstance()->GetData()[i]._type == Quantix::Core::Debugger::TypeLog::INFOS)
			ImGui::TextColored(ImVec4(52 / 255.f, 152 / 255.f, 219 / 255.f, 1), "%s\n", Quantix::Core::Debugger::Logger::GetInstance()->GetData()[i]._message.c_str());
		else if (Quantix::Core::Debugger::Logger::GetInstance()->GetData()[i]._type == Quantix::Core::Debugger::TypeLog::WARNING)
			ImGui::TextColored(ImVec4(241 / 255.f, 196 / 255.f, 15 / 255.f, 1), "%s\n", Quantix::Core::Debugger::Logger::GetInstance()->GetData()[i]._message.c_str());
		else if (Quantix::Core::Debugger::Logger::GetInstance()->GetData()[i]._type == Quantix::Core::Debugger::TypeLog::ERROR)
			ImGui::TextColored(ImVec4(231 / 255.f, 76 / 255.f, 60 / 255.f, 1), "%s\n", Quantix::Core::Debugger::Logger::GetInstance()->GetData()[i]._message.c_str());
		else if (Quantix::Core::Debugger::Logger::GetInstance()->GetData()[i]._type == Quantix::Core::Debugger::TypeLog::PROFILING)
			ImGui::TextColored(ImVec4(39 / 255.f, 174 / 255.f, 96 / 255.f, 1), "%s\n", Quantix::Core::Debugger::Logger::GetInstance()->GetData()[i]._message.c_str());
	}
}

void Editor::DrawConsole(const QXstring& name, ImGuiWindowFlags flags)
{
	ImGui::Begin(name.c_str(), NULL, flags);
	{
		ImGui::BeginTabBar("GPU Infos");
		static QXbool ShowDemoWindow = false;
		// Display GPU infos
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::Checkbox("Demo window", &ShowDemoWindow);

		if (ImGui::CollapsingHeader("System info"))
		{
			ImGui::Text("GL_VERSION: %s", glGetString(GL_VERSION));
			ImGui::Text("GL_RENDERER: %s", glGetString(GL_RENDERER));
			ImGui::Text("GL_SHADING_LANGUAGE_VERSION: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
		}

		if (ShowDemoWindow)
			ImGui::ShowDemoWindow(&ShowDemoWindow);
		ImGui::EndTabBar();

		ImGui::BeginTabBar("Logger");
		PrintLog();
		ImGui::EndTabBar();
	}
	ImGui::End();
}

void Editor::DrawExplorer(const QXstring& name, ImGuiWindowFlags flags)
{
	_explorer.Update(_app->manager, name, flags);
}

void Editor::DrawInspector(const QXstring& name, ImGuiWindowFlags flags)
{
	ImGui::Begin(name.c_str(), NULL, flags);
	{
		if (_hierarchy.GetInspector() != nullptr)
			_hierarchy.GetInspector()->Update(_app);
	}
	ImGui::End();
}
