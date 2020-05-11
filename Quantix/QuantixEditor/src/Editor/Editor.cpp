#include "Editor.h"

#include <fmod.hpp>
#include <fmod_errors.h>

#include <iostream>
#include <MathDefines.h>
#include <Core/UserEntry/InputManager.h>
#include <Core/SoundCore.h>
#include <Physic/PhysicHandler.h>
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
	_play{ QX_TRUE },
	_pause{ QX_TRUE },
	_flagsEditor{}
{
	_cameraEditor = new Quantix::Core::Components::Camera({ 0, 7, -10 }, { 0, -1, 1 }, Math::QXvec3::up);
	_defaultCamera = _mainCamera = new Quantix::Core::Components::Camera({ 0, 7, 10 }, { 0, -1, -1 }, Math::QXvec3::up);
	_lib.load();
	if (!_lib.is_loaded())
		std::cout << _lib.get_error_string() << std::endl;

	//Init Callback
	glfwSetKeyCallback(_win.GetWindow(), IsTriggered);

	_mouseInput = new MouseTest({ QX_FALSE, 0.0f, 0.0f, GetMousePos().x, GetMousePos().y });

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF("Other/Font/Roboto-Medium.otf", 20.0f);
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
   // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;           // Enable Docking

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(_win.GetWindow(), QX_TRUE);
	ImGui_ImplOpenGL3_Init("#version 330");

	InitEditorArtifact();

	_root = _app->scene->GetRoot();

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

	delete _app;
	delete _cameraEditor;
	delete _defaultCamera;
	delete _root;
	delete _mouseInput;
}

void Editor::InitEditorArtifact()
{
	_app = new Quantix::Core::Platform::Application(_win.GetWidth(), _win.GetHeight());
	_app->info.proj = { Math::QXmat4::CreateProjectionMatrix(_app->info.width, _app->info.height, 0.1f, 1000.f, 80.f) };
	_guizmo.Init(_app);
	_console.Init(_app);
}

void Editor::InitImg()
{
	GLFWimage icon;
	icon.pixels = stbi_load("Other/IconEditor/logo_Thomas4.png", &icon.width, &icon.height, 0, STBI_rgb_alpha);

	glfwSetWindowIcon(_win.GetWindow(), 1, &icon);

	_simImg.insert(std::make_pair("Play", _app->manager.CreateTexture("Other/IconEditor/Simulation/Play.png")));
	_simImg.insert(std::make_pair("Pause", _app->manager.CreateTexture("Other/IconEditor/Simulation/Pause.png")));
	_simState.insert(std::make_pair("Play", QX_FALSE));
	_simState.insert(std::make_pair("Pause", QX_FALSE));
}

void Editor::Init()
{
	glfwSetWindowUserPointer(_win.GetWindow(), _mouseInput);

	//Init Scene
	InitScene();

	//Init Editor
	InitEditor();
}

void Editor::InitScene()
{
	Quantix::Core::Components::Light light;
	light.ambient = { 0.3f, 0.3f, 0.3f };
	light.diffuse = { 0.7f, 0.7f, 0.7f };
	light.specular = { 0.7f, 0.7f, 0.7f };
	light.position = { -2.0f, 4.0f, -1.0f };
	light.direction = { 2.0f, -4.0f, 1.f };
	light.constant = 0.5f;
	light.linear = 0.09f;
	light.quadratic = 0.032f;
	light.cutOff = cos(0.70f);
	light.outerCutOff = cos(0.76f);
	light.type = Quantix::Core::Components::ELightType::DIRECTIONAL;

	Quantix::Core::Components::Light light2;
	light2.ambient = { 0.3f, 0.3f, 0.3f };
	light2.diffuse = { 1.0f, 1.0f, 1.0f };
	light2.specular = { 0.50f, 0.50f, 0.50f };
	light2.position = { 0.0f, 2.f, 7.f };
	light2.direction = { 0.0f, 0.f, -1.f };
	light2.constant = 0.5f;
	light2.linear = 0.09f;
	light2.quadratic = 0.032f;
	light2.cutOff = cos(0.70f);
	light2.outerCutOff = cos(0.76f);
	light2.type = Quantix::Core::Components::ELightType::SPOT;

	_lights.push_back(light);
	_lights.push_back(light2);
}

void Editor::InitEditor()
{
	InitImGui();

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

void	Editor::DebugMode()
{
	static QXbool state = false;
	if (GetKey(QX_KEY_F1) == Quantix::Core::UserEntry::EKeyState::PRESSED)
	{
		if (!state)
			ACTIVATE_PROFILING(!GETSTATE_PROFILING());
		state = true;
	}
	if (GetKey(QX_KEY_F1) != Quantix::Core::UserEntry::EKeyState::RELEASED)
		state = false;
}

void Editor::Update()
{
	while (!_win.ShouldClose())
	{
		Quantix::Core::SoundCore::GetInstance()->Update(); //Update for FMOD
		UpdateScene();
	}
}

void Editor::UpdateMouse(Quantix::Core::Components::Camera* camera)
{
	// Mouse state
	{
		Math::QXvec2 mousePos = GetMousePos();

		_mouseInput->DeltaMouseX = mousePos.x - _mouseInput->MouseX;
		_mouseInput->DeltaMouseY = mousePos.y - _mouseInput->MouseY;

		_mouseInput->MouseX = mousePos.x;
		_mouseInput->MouseY = mousePos.y;

		camera->ChangeView(_mouseInput->DeltaMouseX, _mouseInput->DeltaMouseY, _win.GetWidth(), _win.GetHeight(), _app->info.deltaTime);
	}

	// Screen size
	glfwGetWindowSize(_win.GetWindow(), (QXint*)&_app->info.width, (QXint*)&_app->info.height);
}

void	Editor::CameraUpdateEditor()
{
	if (_mouseInput->MouseCaptured)
	{
		UpdateMouse(_cameraEditor);
		if (GetKey(QX_KEY_W) == Quantix::Core::UserEntry::EKeyState::DOWN)
			_cameraEditor->SetPos(_cameraEditor->GetPos() + (_cameraEditor->GetDir() * SPEED));
		if (GetKey(QX_KEY_S) == Quantix::Core::UserEntry::EKeyState::DOWN)
			_cameraEditor->SetPos(_cameraEditor->GetPos() - (_cameraEditor->GetDir() * SPEED));
		if (GetKey(QX_KEY_A) == Quantix::Core::UserEntry::EKeyState::DOWN)
			_cameraEditor->SetPos(_cameraEditor->GetPos() - (_cameraEditor->GetDir().Cross(_cameraEditor->GetUp()) * SPEED));
		if (GetKey(QX_KEY_D) == Quantix::Core::UserEntry::EKeyState::DOWN)
			_cameraEditor->SetPos(_cameraEditor->GetPos() + (_cameraEditor->GetDir().Cross(_cameraEditor->GetUp()) * SPEED));
		_cameraEditor->UpdateLookAt(_cameraEditor->GetPos());
	}
	if (_mainCamera->GetObject() != nullptr)
		_mainCamera->SetPos(((Quantix::Core::DataStructure::GameObject3D*)_mainCamera->GetObject())->GetTransform()->GetPosition());
	_mainCamera->UpdateLookAt(_mainCamera->GetPos());
}

void	Editor::CameraUpdate()
{
	if (_mouseInput->MouseCaptured)
	{
		UpdateMouse(_mainCamera);
		if (GetKey(QX_KEY_W) == Quantix::Core::UserEntry::EKeyState::DOWN)
			_mainCamera->SetPos(_mainCamera->GetPos() + (_mainCamera->GetDir() * SPEED));
		if (GetKey(QX_KEY_S) == Quantix::Core::UserEntry::EKeyState::DOWN)
			_mainCamera->SetPos(_mainCamera->GetPos() - (_mainCamera->GetDir() * SPEED));
		if (GetKey(QX_KEY_A) == Quantix::Core::UserEntry::EKeyState::DOWN)
			_mainCamera->SetPos(_mainCamera->GetPos() - (_mainCamera->GetDir().Cross(_mainCamera->GetUp()) * SPEED));
		if (GetKey(QX_KEY_D) == Quantix::Core::UserEntry::EKeyState::DOWN)
			_mainCamera->SetPos(_mainCamera->GetPos() + (_mainCamera->GetDir().Cross(_mainCamera->GetUp()) * SPEED));
		_mainCamera->UpdateLookAt(_mainCamera->GetPos());
	}
}

void Editor::SaveLoadScene()
{
	static QXbool	sceneChange = false;
	static Quantix::Resources::Scene* newScene = nullptr;

	if ((GetKey(QX_KEY_LEFT_CONTROL) == Quantix::Core::UserEntry::EKeyState::PRESSED || GetKey(QX_KEY_LEFT_CONTROL) == Quantix::Core::UserEntry::EKeyState::DOWN) &&
		(GetKey(QX_KEY_S) == Quantix::Core::UserEntry::EKeyState::PRESSED || GetKey(QX_KEY_S) == Quantix::Core::UserEntry::EKeyState::DOWN))
	{
		_app->manager.SaveScene(_app->scene);
	}
	if (GetKey(QX_KEY_F2) == Quantix::Core::UserEntry::EKeyState::PRESSED)
	{
		Quantix::Physic::PhysicHandler::GetInstance()->CleanScene();
		newScene = _app->manager.LoadScene("../QuantixEngine/Media/scene.quantix");
		sceneChange = true;
	}

	if (sceneChange)
	{
		if (newScene->IsReady())
		{
			_app->scene = newScene;
			_root = _app->scene->GetRoot();
			sceneChange = false;
		}
	}
}

void Editor::UpdateScene()
{
	if (GetKey(QX_KEY_ESCAPE) == Quantix::Core::UserEntry::EKeyState::PRESSED)
	{
		if (_mouseInput->MouseCaptured)
		{
			glfwSetInputMode(_win.GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			_mouseInput->MouseCaptured = false;
		}
	}
	Quantix::Core::UserEntry::InputManager::GetInstance()->Update(_win.GetWindow());

	//Debug For Profiling
	DebugMode();

	START_PROFILING("SaveLoad");
	//Save/Load Scene
	SaveLoadScene();
	STOP_PROFILING("SaveLoad");


	START_PROFILING("Camera");
	//Update Camera
	if (_play)
		CameraUpdate();
	else
		CameraUpdateEditor();
	STOP_PROFILING("Camera");

	std::vector<Quantix::Core::Components::Mesh*>	meshes;
	std::vector<Quantix::Core::Components::ICollider*>	colliders;

	START_PROFILING("Application");
	//Update Application
	if (!_pause && _play)
		_app->Update(meshes, colliders, true);
	else
		_app->Update(meshes, colliders);
	STOP_PROFILING("Application");

	START_PROFILING("Draw");
	//Update Editor + Draw Scene
	if (_play)
		UpdateEditor(_app->renderer.DrawGame(meshes, _lights, _app->info, _mainCamera),
			_app->renderer.Draw(meshes, colliders, _lights, _app->info, _cameraEditor));
	else
		UpdateEditor(_app->renderer.DrawGame(meshes, _lights, _app->info, _mainCamera),
			_app->renderer.Draw(meshes, colliders, _lights, _app->info, _cameraEditor));
	STOP_PROFILING("Draw");

	START_PROFILING("Refresh");
	//Refresh Window
	_win.Refresh(_app->info);
	STOP_PROFILING("Refresh");
}

void Editor::UpdateEditor(QXuint FBOGame, QXuint FBOScene)
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
	START_PROFILING("Editor");
	ImGui::Begin("Editor", NULL, _flagsEditor);

	DrawMenuBar();
	DrawSimulation();
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 1, 1, 1));
	ImGui::DockSpace(_docker.GetIDDockspace(), ImVec2(0, 0), ImGuiDockNodeFlags_NoTabBar);

	ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove;

	for (QXuint i{ 0 }; i < _docker.GetWindowsEditor().size(); i++)
		Draw(_docker.GetWindowsEditor()[i], flags);

	ImGui::PopStyleColor();
	ImGui::End();
	STOP_PROFILING("Editor");

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
			_play = QX_TRUE;
			if (!_activateFocus)
			{
				_mouseInput->MouseCaptured = QX_TRUE;
				glfwSetInputMode(_win.GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

				Math::QXvec2 mousePos = GetMousePos();
				_mouseInput->MouseX = mousePos.x;
				_mouseInput->MouseY = mousePos.y;

				_activateFocus = QX_TRUE;
			}
		}
		else
		{
			_pause = QX_TRUE;
			_activateFocus = QX_FALSE;
		}
	}
	else
	{
		_play = QX_FALSE;
		_pause = QX_FALSE;
		_simState["Pause"] = QX_FALSE;
		_activateFocus = QX_FALSE;
	}
}

void Editor::FocusScene()
{
	if (ImGui::BeginPopupContextWindow("Context Menu", 1, QX_FALSE))
	{
		_mouseInput->MouseCaptured = QX_TRUE;
		glfwSetInputMode(_win.GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		Math::QXvec2 mousePos = GetMousePos();
		_mouseInput->MouseX = mousePos.x;
		_mouseInput->MouseY = mousePos.y;

		ImGui::CloseCurrentPopup();
		ImGui::EndPopup();
	}
}

void Editor::DrawSimulation()
{
	ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove;
	ImGui::BeginChild(ImGui::GetID("Editor"), ImVec2(0, 35), QX_FALSE, flags);
	_guizmo.GuizmoUI();
	Simulation();
	ChangeStateSimulation();
	ImGui::EndChild();
}

void Editor::DrawGame(const QXstring& name, ImGuiWindowFlags flags)
{
	static QXbool focus = QX_FALSE;

	if (!focus)
	{
		if (_play)
		{
			ImGui::SetWindowFocus(name.c_str());
			focus = QX_TRUE;
			_app->scene->Start();
		}
	}
	else if (!_play)
		focus = QX_FALSE;

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
	static QXbool focus = QX_FALSE;
	static QXbool firstTime = QX_FALSE;

	if (!focus)
	{
		if (!_play)
		{
			ImGui::SetWindowFocus(name.c_str());
			if (firstTime)
				focus = QX_TRUE;
			else
				firstTime = QX_TRUE;
		}
	}
	else if (_play)
	{
		focus = QX_FALSE;
		firstTime = QX_FALSE;
	}

	static QXint i = 0;
	ImGui::Begin(name.c_str(), NULL, flags);
	{
		if (i == 0)
		{
			Quantix::Core::Debugger::Logger::GetInstance()->SetError("No Scene load.");
			i++;
		}
		FocusScene();
		ImVec2 size = ImGui::GetWindowSize();
		size.y -= 50;
		ImGui::Image((ImTextureID)(size_t)_fboScene, size, { 0.f, 1.f }, { 1.f, 0.f });
		ImGuizmo::SetDrawlist();
		_guizmo.Update(_hierarchy.GetInspector(), _root, _cameraEditor);
	}
	ImGui::End();
}

void Editor::DrawConsole(const QXstring& name, ImGuiWindowFlags flags)
{
	ImGui::Begin(name.c_str(), NULL, flags);
	{
		_console.Update();
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
		static bool setCamera = QX_FALSE;

		if (_hierarchy.GetInspector() != nullptr)
		{
			if (_root->GetTransform()->FindTransform(_hierarchy.GetInspector()->GetTransform()) == QX_FALSE)
				_hierarchy.GetInspector()->SetEnable(QX_FALSE);
			
			_hierarchy.GetInspector()->Update(_win, _app);
			if (!setCamera)
			{
				if (_hierarchy.GetInspector()->GetTransform()->GetObject()->GetComponents().size() > 0)
				{
					rttr::type type = _hierarchy.GetInspector()->GetTransform()->GetObject()->GetComponents().back()->get_type();
					if (type == rttr::type::get<Quantix::Core::Components::Camera*>().get_raw_type())
					{
						_mainCamera = dynamic_cast<Quantix::Core::Components::Camera*>(_hierarchy.GetInspector()->GetTransform()->GetObject()->GetComponents().back());
						setCamera = QX_TRUE;
					}
				}
			}
		}

	}
	ImGui::End();
}
