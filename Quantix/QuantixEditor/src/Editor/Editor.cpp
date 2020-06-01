#include "Editor.h"

#include <fmod.hpp>
#include <fmod_errors.h>

#include <iostream>
#include <MathDefines.h>
#include <Core/UserEntry/InputManager.h>
#include <Core/Components/CharacterController.h>
#include <Core/DataStructure/GameObject3D.h>
#include <Core/SoundCore.h>
#include <Physic/PhysicHandler.h>
#include <Core/Profiler/Profiler.h>
#include <Core/Components/Behaviours/Arms.h>
#include "stb_image.h"
#include "opengl_helper.h"

Editor::Editor(QXuint width, QXuint height) :
	_win{ width, height },
	_lib{ "QuantixEngine" },
	_docker{},
	_folder{},
	_menuBar{},
	_hierarchy{},
	_play{ QX_FALSE },
	_pause{ QX_FALSE },
	_sceneFocus{ QX_FALSE },
	_gameFocus{ QX_FALSE },
	_maximize{ QX_FALSE },
	_flagsEditor{}
{
	_cameraEditor = new Quantix::Core::Components::Camera({ 0, 7, -10 }, { 0, -1, 1 }, Math::QXvec3::up);
	_defaultCamera = _mainCamera = new Quantix::Core::Components::Camera({ 0, 7, 10 }, { 0, -1, -1 }, Math::QXvec3::up);
	_lib.load();
	if (!_lib.is_loaded())
		std::cout << _lib.get_error_string() << std::endl;

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

	_app->renderer.CreateRenderFramebuffer(width, height, _sceneBuffer);
	_app->renderer.CreateRenderFramebuffer(width, height, _gameBuffer);

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
	if (_defaultCamera == _mainCamera)
		delete _defaultCamera;
	else
	{
		delete _mainCamera;
		delete _defaultCamera;
	}
	delete _mouseInput;
}

void Editor::InitEditorArtifact()
{
	_app = new Quantix::Core::Platform::Application(_win.GetWidth(), _win.GetHeight());
	_app->info.proj = { Math::QXmat4::CreateProjectionMatrix(_app->info.width, _app->info.height, 0.1f, 1000.f, 60.f) };
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
	_command.insert(std::make_pair("Grab", _app->manager.CreateTexture("Other/IconEditor/Simulation/E.png")));
	_command.insert(std::make_pair("Change Power", _app->manager.CreateTexture("Other/IconEditor/Simulation/Tab.png")));
	_command.insert(std::make_pair("Launch Object", _app->manager.CreateTexture("Other/IconEditor/Simulation/LeftMouseClick.png")));
	_command.insert(std::make_pair("Use Power", _app->manager.CreateTexture("Other/IconEditor/Simulation/RightMouseClick.png")));
}

void Editor::Init()
{
	glfwSetWindowUserPointer(_win.GetWindow(), _mouseInput);

	//Init Editor
	InitEditor();
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
	if (_sceneFocus)
	{
		if (_mouseInput->MouseCaptured)
		{
			UpdateMouse(_cameraEditor);
			if (GetKey(QX_KEY_W) == Quantix::Core::UserEntry::EKeyState::DOWN)
				_cameraEditor->SetPos(_cameraEditor->GetPos() + (_cameraEditor->GetDir() * SPEEDFREECAM * (QXfloat)_app->info.deltaTime));
			if (GetKey(QX_KEY_S) == Quantix::Core::UserEntry::EKeyState::DOWN)
				_cameraEditor->SetPos(_cameraEditor->GetPos() - (_cameraEditor->GetDir() * SPEEDFREECAM * (QXfloat)_app->info.deltaTime));
			if (GetKey(QX_KEY_A) == Quantix::Core::UserEntry::EKeyState::DOWN)
				_cameraEditor->SetPos(_cameraEditor->GetPos() - (_cameraEditor->GetDir().Cross(_cameraEditor->GetUp()) * SPEEDFREECAM * (QXfloat)_app->info.deltaTime));
			if (GetKey(QX_KEY_D) == Quantix::Core::UserEntry::EKeyState::DOWN)
				_cameraEditor->SetPos(_cameraEditor->GetPos() + (_cameraEditor->GetDir().Cross(_cameraEditor->GetUp()) * SPEEDFREECAM * (QXfloat)_app->info.deltaTime));
			_cameraEditor->UpdateLookAt(_cameraEditor->GetPos());
		}
		if (_mainCamera->GetObject() != nullptr)
			_mainCamera->SetPos(((Quantix::Core::DataStructure::GameObject3D*)_mainCamera->GetObject())->GetTransform()->GetPosition());
		_mainCamera->UpdateLookAt(_mainCamera->GetPos());
	}
}

void	Editor::MovePlayerController()
{
	Math::QXvec3 dir = _mainCamera->GetDir();
	dir.y = 0.f;
	dir = dir.Normalize();
	if (GetKey(QX_KEY_W) == Quantix::Core::UserEntry::EKeyState::DOWN)
		_mainCamera->_controller->_velocity += dir;
	if (GetKey(QX_KEY_S) == Quantix::Core::UserEntry::EKeyState::DOWN)
		_mainCamera->_controller->_velocity -= dir;
	if (GetKey(QX_KEY_A) == Quantix::Core::UserEntry::EKeyState::DOWN)
		_mainCamera->_controller->_velocity -= dir.Cross(_mainCamera->GetUp());
	if (GetKey(QX_KEY_D) == Quantix::Core::UserEntry::EKeyState::DOWN)
		_mainCamera->_controller->_velocity += dir.Cross(_mainCamera->GetUp());
	if (GetKey(QX_KEY_SPACE) == Quantix::Core::UserEntry::EKeyState::PRESSED && !_mainCamera->_controller->CheckIsFalling())
		_mainCamera->_controller->_velocity += _mainCamera->_controller->GetUpDirection() * 30;

	_mainCamera->_controller->_velocity.y *= 0.95f;

	_mainCamera->_controller->Move((GRAVITY + _mainCamera->_controller->_velocity) * (QXfloat)_app->info.deltaTime, 0, (QXfloat)_app->info.deltaTime);
	_mainCamera->_controller->_velocity.x = 0.f;
	_mainCamera->_controller->_velocity.z = 0.f;
}

void	Editor::MoveFreeCam()
{
	if (GetKey(QX_KEY_W) == Quantix::Core::UserEntry::EKeyState::DOWN)
		_mainCamera->SetPos(_mainCamera->GetPos() + (_mainCamera->GetDir() * SPEEDFREECAM * (QXfloat)_app->info.deltaTime));
	if (GetKey(QX_KEY_S) == Quantix::Core::UserEntry::EKeyState::DOWN)
		_mainCamera->SetPos(_mainCamera->GetPos() - (_mainCamera->GetDir() * SPEEDFREECAM * (QXfloat)_app->info.deltaTime));
	if (GetKey(QX_KEY_A) == Quantix::Core::UserEntry::EKeyState::DOWN)
		_mainCamera->SetPos(_mainCamera->GetPos() - (_mainCamera->GetDir().Cross(_mainCamera->GetUp()) * SPEEDFREECAM * (QXfloat)_app->info.deltaTime));
	if (GetKey(QX_KEY_D) == Quantix::Core::UserEntry::EKeyState::DOWN)
		_mainCamera->SetPos(_mainCamera->GetPos() + (_mainCamera->GetDir().Cross(_mainCamera->GetUp()) * SPEEDFREECAM * (QXfloat)_app->info.deltaTime));
}

void	Editor::CameraUpdate()
{
	if (_gameFocus)
	{
		if (_mouseInput->MouseCaptured)
		{
			UpdateMouse(_mainCamera);
			if (_mainCamera->_controller)
			{
				MovePlayerController();
				_mainCamera->UpdateLookAt(_mainCamera->GetPos());
			}
			else
			{
				MoveFreeCam();
				_mainCamera->UpdateLookAt(_mainCamera->_pos);
			}
		}
	}
}

void Editor::CheckNewSceneCamera(Quantix::Core::DataStructure::GameObject3D* object)
{
	for (auto it = object->GetTransform()->GetChilds().begin(); it != object->GetTransform()->GetChilds().end(); ++it)
	{
		if ((*it)->GetChilds().size() > 0)
			CheckNewSceneCamera((*it)->GetObject());

		if ((*it)->GetObject()->GetComponent<Quantix::Core::Components::Camera>())
		{
			for (auto it = _hasCamera.begin(); it != _hasCamera.end();)
			{
				if (!_root->GetTransform()->FindTransform(it->second->GetTransform()))
					it = _hasCamera.erase(it);
				else if (it->second->GetComponent<Quantix::Core::Components::Camera>() == nullptr)
					it = _hasCamera.erase(it);
				else
					++it;
			}
			_hasCamera.insert(std::make_pair(QX_TRUE, (*it)->GetObject()));
			_mainCamera = (*it)->GetObject()->GetComponent<Quantix::Core::Components::Camera>();
			break;
		}
	}
}

void Editor::SaveLoadScene()
{
	if ((GetKey(QX_KEY_LEFT_CONTROL) == Quantix::Core::UserEntry::EKeyState::PRESSED || GetKey(QX_KEY_LEFT_CONTROL) == Quantix::Core::UserEntry::EKeyState::DOWN) &&
		(GetKey(QX_KEY_S) == Quantix::Core::UserEntry::EKeyState::PRESSED || GetKey(QX_KEY_S) == Quantix::Core::UserEntry::EKeyState::DOWN))
	{
		_app->manager.SaveScene(_app->scene);
	}

	if (GetKey(QX_KEY_F2) == Quantix::Core::UserEntry::EKeyState::PRESSED)
	{
		Quantix::Physic::PhysicHandler::GetInstance()->CleanScene();
		_app->newScene = _app->manager.LoadScene("../QuantixEngine/Media/scene.quantix");
		_app->sceneChange = true;
	}

	if (_app->sceneChange)
	{
		if (_app->newScene->IsReady())
		{
			_app->scene = _app->newScene;
			_root = _app->scene->GetRoot();
			_app->sceneChange = false;
			_app->newScene = nullptr;
			CheckNewSceneCamera(_root);
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
			_mouseInput->MouseCaptured = QX_FALSE;
			_gameFocus = _sceneFocus = QX_FALSE;
		}
	}
	Quantix::Core::UserEntry::InputManager::GetInstance()->Update(_win.GetWindow());

	//Debug For Profiling
	DebugMode();

	START_PROFILING("SaveLoad");
	//Save/Load Scene
	SaveLoadScene();
	STOP_PROFILING("SaveLoad");

	std::vector<Quantix::Core::Components::Mesh*>	meshes;
	std::vector<Quantix::Core::Components::ICollider*>	colliders;
	_lights.clear();

	START_PROFILING("Application");
	//Update Application
	if (!_pause && _play)
		_app->Update(meshes, colliders, _lights, true);
	else
		_app->Update(meshes, colliders, _lights);
	STOP_PROFILING("Application");

	START_PROFILING("Camera");
	//Update Camera
	CameraUpdate();
	CameraUpdateEditor();
	STOP_PROFILING("Camera");

	START_PROFILING("Draw");
	_app->renderer.Draw(meshes, colliders, _lights, _app->info, _mainCamera, _gameBuffer, false);
	_app->renderer.Draw(meshes, colliders, _lights, _app->info, _cameraEditor, _sceneBuffer, true);
	//Update Editor + Draw Scene
	UpdateEditor();
	STOP_PROFILING("Draw");

	START_PROFILING("Refresh");
	//Refresh Window
	_win.Refresh(_app->info);
	STOP_PROFILING("Refresh");
}

void Editor::UpdateEditor()
{
	InitImGui();

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
	_menuBar.Update(_app);
}

void Editor::DrawHierarchy(const QXstring& name, ImGuiWindowFlags flags)
{
	_hierarchy.Update(name, flags, _root->GetTransform(), _app);
}

QXstring Editor::GetNameOfShader(QXstring shaderPath)
{
	QXuint pos = shaderPath.find_last_of("/");
	QXstring fileName = shaderPath.substr(pos + 1);
	QXstring name = fileName.substr(0, fileName.size() - 5);
	if (name == "fragmentShader")
		name = "Default";
	return name;
}

void Editor::DrawShader(const QXstring& name, ImGuiWindowFlags flags)
{
	ImGui::Begin(name.c_str(), NULL, flags);
	{
		if (_app->manager.GetShaders().size() > 0)
		{
			std::unordered_map<QXstring, QXuint>	ShaderID;
			std::list<QXstring>						ShaderName;
			for (auto it = _app->manager.GetShaders().begin(); it != _app->manager.GetShaders().end(); ++it)
			{
				ShaderID.insert(std::make_pair(GetNameOfShader(it->first), it->second->GetID()));
				ShaderName.push_back(GetNameOfShader(it->first));
			}
			ShaderName.sort();
			for (auto it = ShaderName.begin(); it != ShaderName.end(); ++it)
			{
				if (ImGui::TreeNode((*it).c_str()))
				{
					InspectProgram(ShaderID[(*it)]);
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
			_pause = QX_FALSE;
		}
		else
			_pause = QX_TRUE;
	}
	else
	{
		_play = QX_FALSE;
		_pause = QX_FALSE;
		_simState["Pause"] = QX_FALSE;
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

void Editor::MaximizeOnPlay()
{
	QXfloat posX = ImGui::GetWindowSize().x / 2 + 70;
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0, 0, 0, 1));
	if (_maximize)
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(44 / 255, 62 / 255, 80 / 255, 1));
	else
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(128 / 255.f, 128 / 255.f, 128 / 255.f, 1));
	ImGui::SetCursorPos(ImVec2(posX, 0));
	if (ImGui::Button("Maximize", ImVec2(80, 30)))
		_maximize = !_maximize;
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
}

void Editor::DrawSimulation()
{
	ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove;
	ImGui::BeginChild(ImGui::GetID("Editor"), ImVec2(0, 35), QX_FALSE, flags);
	_guizmo.GuizmoUI();
	Simulation();
	MaximizeOnPlay();
	ChangeStateSimulation();
	ImGui::EndChild();
}

void Editor::PrintPower()
{
	ImGui::SetCursorPos(ImVec2(20, ImGui::GetWindowSize().y - 45));
	switch (_mainCamera->GetObject()->GetComponent<Quantix::Gameplay::Arms>()->GetPower())
	{
		case Quantix::Gameplay::EArmState::FREEZE:
			ImGui::Text("Freeze");
			break;
		case Quantix::Gameplay::EArmState::MAGNET_NEG:
			ImGui::Text("Repulsion");
			break;
		case Quantix::Gameplay::EArmState::MAGNET_POS:
			ImGui::Text("Attraction");
			break;
		default:
			break;
	}
	QXfloat posY = ImGui::GetWindowSize().y - 150.f;
	for (auto it = _command.begin(); it != _command.end(); ++it)
	{
		ImGui::SetCursorPos(ImVec2(ImGui::GetWindowSize().x - 250.f, posY));
		QXstring text = it->first + ": ";
		ImGui::Text(text.c_str()); ImGui::SameLine(ImGui::GetWindowSize().x - 70.f);
		if (it->first == "Grab")
			ImGui::Image((ImTextureID)it->second->GetId(), ImVec2(30, 30), ImVec2(0, 1), ImVec2(1, 0));
		else if (it->first == "Change Power")
			ImGui::Image((ImTextureID)it->second->GetId(), ImVec2(40, 30), ImVec2(0, 1), ImVec2(1, 0));
		else
			ImGui::Image((ImTextureID)it->second->GetId(), ImVec2(20, 30), ImVec2(0, 1), ImVec2(1, 0));
		posY += 35.f;
	}
}

void Editor::DrawGame(const QXstring& name, ImGuiWindowFlags flags)
{
	if (_maximize && _play)
	{
		ImGui::SetNextWindowPos(ImVec2(0, 75));
		ImVec2 size = ImGui::GetWindowSize();
		size.y -= 75;
		ImGui::SetNextWindowSize(size);
		ImGui::Begin("MyGame", NULL, flags);
	}
	else
		ImGui::Begin(name.c_str(), NULL, flags);
	{
		ImGui::SetWindowFontScale(1.5f);
		if (_play && !_pause)
		{
			FocusScene();
			_gameFocus = QX_TRUE;
			_sceneFocus = QX_FALSE;
		}
		ImVec2 size = ImGui::GetWindowSize();
		size.y -= 50;
		ImGui::Image((ImTextureID)(size_t)_gameBuffer.texture[0], size, { 0.f, 1.f }, { 1.f, 0.f });
		if (_mainCamera->GetObject())
		{
			if (_mainCamera->GetObject()->GetComponent<Quantix::Gameplay::Arms>(true))
				PrintPower();
		}
	}
	ImGui::End();
}

void Editor::DrawScene(const QXstring& name, ImGuiWindowFlags flags)
{
	static QXint i = 0;
	ImGui::Begin(name.c_str(), NULL, flags);
	{
		if (_pause || !_play)
		{
			FocusScene();
			_sceneFocus = QX_TRUE;
			_gameFocus = QX_FALSE;
		}
		ImVec2 size = ImGui::GetWindowSize();
		size.y -= 50;
		ImGui::Image((ImTextureID)(size_t)_sceneBuffer.texture[0], size, { 0.f, 1.f }, { 1.f, 0.f });
		ImGuizmo::SetDrawlist();
		_guizmo.Update(_hierarchy.GetInspector(), _root, _cameraEditor);
	}
	ImGui::End();
}

void Editor::DrawConsole(const QXstring& name, ImGuiWindowFlags flags)
{
	_console.Update(name, flags);
}

void Editor::DrawExplorer(const QXstring& name, ImGuiWindowFlags flags)
{
	_explorer.Update(_app->manager, name, flags);
}

void Editor::CheckCamera()
{
	if (_hasCamera.size() == 0)
	{
		if (_hierarchy.GetInspector()->Get3D())
		{
			if (((Quantix::Core::DataStructure::GameObject3D*)_hierarchy.GetInspector()->GetGameComponent())->GetComponent<Quantix::Core::Components::Camera>() != nullptr)
			{
				_mainCamera = ((Quantix::Core::DataStructure::GameObject3D*)_hierarchy.GetInspector()->GetGameComponent())->GetComponent<Quantix::Core::Components::Camera>();
				_hasCamera.insert(std::make_pair(QX_TRUE, (Quantix::Core::DataStructure::GameObject3D*)_hierarchy.GetInspector()->GetGameComponent()));
			}
			else
				_mainCamera = _defaultCamera;
		}
	}
	else
	{
		for (auto it = _hasCamera.begin(); it != _hasCamera.end();)
		{
			if (!_root->GetTransform()->FindTransform(it->second->GetTransform()))
				it = _hasCamera.erase(it);
			else if (it->second->GetComponent<Quantix::Core::Components::Camera>() == nullptr)
				it = _hasCamera.erase(it);
			else
				++it;
		}
	}
}

void Editor::DrawInspector(const QXstring& name, ImGuiWindowFlags flags)
{
	ImGui::Begin(name.c_str(), NULL, flags);
	{
		if (_hierarchy.GetInspector() != nullptr)
		{
			if (_hierarchy.GetInspector()->Get3D())
			{
				if (_root->GetTransform()->FindTransform(_hierarchy.GetInspector()->GetTransform3D()) == QX_FALSE)
					_hierarchy.GetInspector()->SetEnable(QX_FALSE);
			}
			else if (_hierarchy.GetInspector()->Get2D())
			{
				if (_app->scene->GetRoot2D()->GetTransform()->FindTransform(_hierarchy.GetInspector()->GetTransform2D()) == QX_FALSE)
					_hierarchy.GetInspector()->SetEnable(QX_FALSE);
			}
			else
			{
				if (_app->scene->FindGameComponent(_hierarchy.GetInspector()->GetGameComponent()) == QX_FALSE)
					_hierarchy.GetInspector()->SetEnable(QX_FALSE);
			}
			
			_hierarchy.GetInspector()->Update(_win, _app);
			CheckCamera();
		}
	}
	ImGui::End();
}
