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
	_lib{ "QuantixEngine" },
	_docker{},
	_folder{},
	_menuBar{},
	_hierarchy{},
	_play{ false },
	_pause{ false }, 
	_guizmoType{ ImGuizmo::OPERATION::TRANSLATE },
	_guizmoMode{ ImGuizmo::MODE::WORLD },
	_sizeLog{ 0 },
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

	_app = new Quantix::Core::Platform::Application(_win.GetWidth(), _win.GetHeight());

	_root = _app->scene->GetRoot();

	_showTypeLog.push_back(true);
	_showTypeLog.push_back(true);
	_showTypeLog.push_back(true);
	InitImg();
}


Editor::~Editor()
{
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	//unload lib rttr
	_lib.unload();
}

void Editor::InitImg()
{
	GLFWimage icon;
	icon.pixels = stbi_load("media/IconEditor/logo_6_1.png", &icon.width, &icon.height, 0, STBI_rgb_alpha);

	glfwSetWindowIcon(_win.GetWindow(), 1, &icon);

	_simImg.insert(std::make_pair("Play", _app->manager.CreateTexture("media/IconEditor/Simulation/Play.png")));
	_simImg.insert(std::make_pair("Pause", _app->manager.CreateTexture("media/IconEditor/Simulation/Pause.png")));
	_simState.insert(std::make_pair("Play", false));
	_simState.insert(std::make_pair("Pause", false));
	_imgGuizmo.push_back(_app->manager.CreateTexture("media/IconEditor/Simulation/Translate.png"));
	_imgGuizmo.push_back(_app->manager.CreateTexture("media/IconEditor/Simulation/Rotate.png"));
	_imgGuizmo.push_back(_app->manager.CreateTexture("media/IconEditor/Simulation/Scale.png"));
	_imgTypeLog.push_back(_app->manager.CreateTexture("media/IconEditor/Simulation/info.png"));
	_imgTypeLog.push_back(_app->manager.CreateTexture("media/IconEditor/Simulation/warning.png"));
	_imgTypeLog.push_back(_app->manager.CreateTexture("media/IconEditor/Simulation/error.png"));
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

void Editor::Update(QXuint FBOGame, QXuint FBOScene)
{
	InitImGui();

	_fboScene = FBOScene;
	_fboGame = FBOGame;
	static QXint i = 0;
	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::SetNextWindowViewport(viewport->ID);

	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 6.f);
	ImGui::PushStyleColor(ImGuiCol_MenuBarBg, ImVec4(1, 1, 1, 1));
	ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1, 1, 1, 1));
	ImGui::Begin("Editor", NULL, _flagsEditor);

	START_PROFILING("Editor");

	DrawMenuBar();
	DrawSimulation();
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 1, 1, 1));
	ImGui::DockSpace(_docker.GetIDDockspace(), ImVec2(0, 0), ImGuiDockNodeFlags_NoTabBar);

	ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove;

	for (QXuint i{ 0 }; i < _docker.GetWindowsEditor().size(); i++)
		Draw(_docker.GetWindowsEditor()[i], flags);

	ImGui::PopStyleColor();
	STOP_PROFILING("Editor");
	ImGui::End();

	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleVar();

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
	else if (name == "Game")
		DrawGame(name, flags);
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
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(128 / 255.f, 128 / 255.f, 128 / 255.f, 1));
		else
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(44 / 255, 62 / 255, 80 / 255, 1));
		ImGui::SetCursorPos(ImVec2(ImGui::GetWindowSize().x / 2 + pos, 0));
		if (ImGui::ImageButton((ImTextureID)_simImg[it->first]->GetId(), ImVec2(25, 25)))
			it->second = !it->second;
		ImGui::PopStyleColor();
		pos *= -1;
	}
}

void Editor::ChangeStateSimulation()
{
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
}

void Editor::ChangeGuizmoOperation(QXuint index)
{
	if (index == 0)
		_guizmoType = ImGuizmo::OPERATION::TRANSLATE;
	else if (index == 1)
		_guizmoType = ImGuizmo::OPERATION::ROTATE;
	else
		_guizmoType = ImGuizmo::OPERATION::SCALE;
}

void Editor::LocalWorldGuizmo(QXint pos)
{
	pos += 20;
	ImGui::SetCursorPos(ImVec2(pos, 0));
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0, 0, 0, 1));

	if (_guizmoMode == ImGuizmo::MODE::LOCAL)
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(44 / 255, 62 / 255, 80 / 255, 1));
	else
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(128 / 255.f, 128 / 255.f, 128 / 255.f, 1));


	if (ImGui::Button("Local"))
		_guizmoMode = ImGuizmo::MODE::LOCAL;

	ImGui::PopStyleColor();
	pos += 50;
	ImGui::SetCursorPos(ImVec2(pos, 0));

	if (_guizmoMode == ImGuizmo::MODE::WORLD)
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(44 / 255, 62 / 255, 80 / 255, 1));
	else
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(128 / 255.f, 128 / 255.f, 128 / 255.f, 1));

	if (ImGui::Button("World"))
		_guizmoMode = ImGuizmo::MODE::WORLD;

	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
}

void Editor::GuizmoUI()
{
	QXint pos = 0;
	for (QXuint i = 0; i < _imgGuizmo.size(); i++)
	{
		ImGui::SetCursorPos(ImVec2(pos, 0));
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(128 / 255.f, 128 / 255.f, 128 / 255.f, 1));
			if (ImGui::ImageButton((ImTextureID)_imgGuizmo[i]->GetId(), ImVec2(20, 20)))
				ChangeGuizmoOperation(i);
		pos += 30;
		ImGui::PopStyleColor();
	}

	LocalWorldGuizmo(pos);
}

void Editor::DrawSimulation()
{
	ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove;
	ImGui::BeginChild(ImGui::GetID("Editor"), ImVec2(0, 35), false, flags);
	GuizmoUI();
	Simulation();
	ChangeStateSimulation();
	ImGui::EndChild();
}

void Editor::MoveObject(Quantix::Physic::Transform3D* transform, Math::QXmat4& matrix, Math::QXmat4& matrixTmp)
{
	Math::QXmat4 matrixTmp2 = Math::QXmat4::CreateTRSMatrix(transform->GetPosition(), Math::QXquaternion(1, 0, 0, 0), transform->GetScale());
	Math::QXvec3 translation, transTmp, rotation, rotTmp, scale, scaleTmp;

	if (_guizmoType == ImGuizmo::OPERATION::TRANSLATE)
	{
		ImGuizmo::Manipulate(_cameraEditor->GetLookAt().array, _app->info.proj.array, ImGuizmo::OPERATION::TRANSLATE, _guizmoMode, matrix.array);
		ImGuizmo::DecomposeMatrixToComponents(matrixTmp.array, transTmp.e, rotation.e, scale.e);
		ImGuizmo::DecomposeMatrixToComponents(matrix.array, translation.e, rotation.e, scale.e);
		transform->Translate(translation - transTmp);
	}
	else if (_guizmoType == ImGuizmo::OPERATION::ROTATE)
	{
		ImGuizmo::Manipulate(_cameraEditor->GetLookAt().array, _app->info.proj.array, ImGuizmo::OPERATION::ROTATE, _guizmoMode, matrixTmp2.array);
		
		ImGuizmo::DecomposeMatrixToComponents(matrixTmp2.array, translation.e, rotTmp.e, scale.e);
		rotTmp = rotTmp * (Q_PI / 180);

		transform->Rotate(Math::QXquaternion::EulerToQuaternion(rotTmp));
	}
	else
	{
		ImGuizmo::Manipulate(_cameraEditor->GetLookAt().array, _app->info.proj.array, ImGuizmo::OPERATION::SCALE, _guizmoMode, matrix.array);
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

	QXfloat dist = (transform->GetPosition() - _cameraEditor->GetPos()).Length();

	ImGuizmo::SetRect(pos.x, pos.y, size.x, size.y);
	pos.y += 25;
	ImGuizmo::ViewManipulate(_cameraEditor->GetLookAt().array, dist, pos, ImVec2(128,128), 0x10101010);

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

void Editor::FocusScene()
{
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
}

void Editor::DrawGame(const QXstring& name, ImGuiWindowFlags flags)
{
	static QXbool focus = false;

	if (!focus)
	{
		if (_play)
		{
			ImGui::SetWindowFocus(name.c_str());
			focus = true;
		}
	}
	else if (!_play)
		focus = false;

	ImGui::Begin(name.c_str(), NULL, flags);
	{
		FocusScene();
		ImVec2 size = ImGui::GetWindowSize();
		size.y -= 50;
		ImGui::Image((ImTextureID)(size_t)_fboGame, size, { 0.f, 1.f }, { 1.f, 0.f });
	}
	ImGui::End();
}

void Editor::DrawScene(const QXstring& name, ImGuiWindowFlags flags)
{
	static QXbool focus = false;

	if (!focus)
	{
		if (!_play)
		{
			ImGui::SetWindowFocus(name.c_str());
			focus = true;
		}
	}
	else if (_play)
		focus = false;
	static QXint i = 0;
	ImGui::Begin(name.c_str(), NULL, flags);
	{
		ImGuizmo::SetDrawlist();
		if (i == 0)
		{
			Quantix::Core::Debugger::Logger::GetInstance()->SetError("No Scene load.");
			i++;
		}
		FocusScene();
		ImVec2 size = ImGui::GetWindowSize();
		size.y -= 50;
		ImGui::Image((ImTextureID)(size_t)_fboScene, size, { 0.f, 1.f }, { 1.f, 0.f });
		DrawGuizmo();
	}
	ImGui::End();
}

void Editor::PrintLog()
{
	ImGuiStyle& style = ImGui::GetStyle();
	for (QXuint i = 0; i < Quantix::Core::Debugger::Logger::GetInstance()->GetData().size(); i++)
	{
		if (Quantix::Core::Debugger::Logger::GetInstance()->GetData()[i]._type == Quantix::Core::Debugger::TypeLog::INFOS && _showTypeLog[0])
			ImGui::TextColored(ImVec4(52 / 255.f, 152 / 255.f, 219 / 255.f, 1), "%s\n", Quantix::Core::Debugger::Logger::GetInstance()->GetData()[i]._message.c_str());
		else if (Quantix::Core::Debugger::Logger::GetInstance()->GetData()[i]._type == Quantix::Core::Debugger::TypeLog::WARNING && _showTypeLog[1])
			ImGui::TextColored(ImVec4(241 / 255.f, 196 / 255.f, 15 / 255.f, 1), "%s\n", Quantix::Core::Debugger::Logger::GetInstance()->GetData()[i]._message.c_str());
		else if (Quantix::Core::Debugger::Logger::GetInstance()->GetData()[i]._type == Quantix::Core::Debugger::TypeLog::ERROR && _showTypeLog[2])
			ImGui::TextColored(ImVec4(231 / 255.f, 76 / 255.f, 60 / 255.f, 1), "%s\n", Quantix::Core::Debugger::Logger::GetInstance()->GetData()[i]._message.c_str());
		else if (Quantix::Core::Debugger::Logger::GetInstance()->GetData()[i]._type == Quantix::Core::Debugger::TypeLog::PROFILING)
			ImGui::TextColored(ImVec4(39 / 255.f, 174 / 255.f, 96 / 255.f, 1), "%s\n", Quantix::Core::Debugger::Logger::GetInstance()->GetData()[i]._message.c_str());
	}
	if (Quantix::Core::Debugger::Logger::GetInstance()->GetData().size() != _sizeLog)
	{
		_sizeLog = Quantix::Core::Debugger::Logger::GetInstance()->GetData().size();
		ImGui::SetScrollHereY(1.f);
	}
}

void Editor::ConsoleUI()
{
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(192 / 255.f, 57 / 255.f, 43 / 255.f, 1.f));
	if (ImGui::Button("Clear", ImVec2(75,0)))
		Quantix::Core::Debugger::Logger::GetInstance()->ClearMessage();
	ImGui::PopStyleColor();
	ImGui::SameLine();
	ImGui::Dummy(ImVec2(20,20));
	for (QXuint i = 0; i < _showTypeLog.size(); i++)
	{
		ImGui::SameLine();
		ImGui::BeginGroup();
		if (ImGui::ImageButton((ImTextureID)_imgTypeLog[i]->GetId(), ImVec2(20,20), ImVec2(0,1), ImVec2(1,0)))
			_showTypeLog[i] = !_showTypeLog[i];
		ImGui::SameLine();
		ImGui::Text("%d", Quantix::Core::Debugger::Logger::GetInstance()->GetMessage()[i]);
		ImGui::EndGroup();
	}
}

void Editor::DrawConsole(const QXstring& name, ImGuiWindowFlags flags)
{
	ImGui::Begin(name.c_str(), NULL, flags);
	{
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

		ImGui::BeginTabBar("Log");
		ConsoleUI();
		ImGui::BeginChild("Logger");
		PrintLog();
		ImGui::EndChild();
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
			_hierarchy.GetInspector()->Update(_win, _app);
	}
	ImGui::End();
}
