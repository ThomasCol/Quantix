#include "Editor.h"
#include <iostream>
#include "Logger.h"
#include "Profiler.h"
#include "stb_image.h"


Editor::Editor(QXuint width, QXuint height) :
	_win{width, height},
	_docker{},
	_folder{},
	_menuBar{},
	_hierarchy{},
	_init{ false },
	_flagsEditor{}
{
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

	_app = new Quantix::Core::Platform::Application(_win.GetWidth(), _win.GetHeight(), _win.GetResizeCallback());

	_simImg.push_back(_app->manager.CreateTexture("media/IconEditor/Play.png"));
	_simImg.push_back(_app->manager.CreateTexture("media/IconEditor/Pause.png"));
	_simState.push_back(false);
	_simState.push_back(false);
}

Editor::~Editor()
{
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

bool Editor::Init()
{
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	if (!_init)
	{
		ImGui::GetStyle().WindowRounding = 0.f;
		_flagsEditor = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoCollapse;
		ImGui::Begin("Quantix Editor", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove);

		DrawSimulation();

		_docker.Init();
		ImGui::DockSpace(_docker.GetIDDockspace(), ImVec2(0, 0), ImGuiDockNodeFlags_NoTabBar);

		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		_init = true;

		return false;
	}
	return true;
}

void Editor::Update(QXuint FBO)
{
	_fbo = FBO;
	static QXint i = 0;
	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::SetNextWindowViewport(viewport->ID);

	ImGui::PushStyleColor(ImGuiCol_MenuBarBg, ImVec4(1, 1, 1, 1));
	ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1, 1, 1, 1));
	ImGui::Begin("Editor", NULL, _flagsEditor);

	if (i == 0)
		Quantix::Core::Profiling::Profiler::GetInstance()->StartProfiling("Editor");

	DrawMenuBar();
	DrawSimulation();
	ImGui::DockSpace(_docker.GetIDDockspace(), ImVec2(0, 0), ImGuiDockNodeFlags_NoTabBar);

	ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove;

	Quantix::Core::Profiling::Profiler::GetInstance()->SetMessage("Editor", "Draw Editor\n");

	for (QXuint i{ 0 }; i < _docker.GetWindowsEditor().size(); i++)
		Draw(_docker.GetWindowsEditor()[i], flags);

	if (i == 0)
	{
		Quantix::Core::Profiling::Profiler::GetInstance()->StopProfiling("Editor");
		i++;
	}
	ImGui::End();

	ImGui::PopStyleColor();
	ImGui::PopStyleColor();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Editor::Draw(QXstring name, ImGuiWindowFlags flags)
{
	if (name == "Console")
		DrawConsole(name, flags);
	else if (name == "Explorer")
		DrawExplorer(name, flags);
	else if (name == "Scene")
		DrawScene(name, flags);
	else if (name == "Hierarchy")
		DrawHierarchy(name, flags);
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
	_menuBar.Update(_object);
	//_menuBar.Update(_gameComponent);
}

void Editor::DrawHierarchy(QXstring name, ImGuiWindowFlags flags)
{
	_hierarchy.Update(name, flags, _object);
	//_hierarchy.Update(name, flags, _gameComponent);
}

void Editor::Simulation()
{
	QXint pos = -20;
	for (QXuint i{ 0 }; i < _simImg.size(); i++)
	{
		QXbool state = _simState[i];
		if (!_simState[i])
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1, 1, 1, 1));
		else
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(44 / 255, 62 / 255, 80 / 255, 1));
		ImGui::SetCursorPos(ImVec2(ImGui::GetWindowSize().x / 2 + pos, 0));
		if (ImGui::ImageButton((ImTextureID)_simImg[i]->GetId(), ImVec2(25, 25)))
			_simState[i] = !_simState[i];
		ImGui::PopStyleColor();

		pos *= -1;
	}
}

void Editor::DrawSimulation()
{
	ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove;
	ImGui::BeginChild(ImGui::GetID("Editor"), ImVec2(0, 35), false, flags);
	Simulation();
	ImGui::EndChild();

}

void Editor::DrawScene(QXstring name, ImGuiWindowFlags flags)
{
	static QXint i = 0;

	ImGui::Begin(name.c_str(), NULL, flags);
	{
		if (i == 0)
		{
			Quantix::Core::Debugger::Logger::GetInstance()->SetError("No Scene load.");
			i++;
		}
		ImGui::Image((ImTextureID)(size_t)_fbo, ImGui::GetWindowSize(), { 0.f, 1.f }, { 1.f, 0.f });
	}
	ImGui::End();
}

void Editor::PrintLog()
{
	ImGuiStyle& style = ImGui::GetStyle();
	for (QXuint i = 0; i < Quantix::Core::Debugger::Logger::GetInstance()->GetData().size(); i++)
	{
		if (Quantix::Core::Debugger::Logger::GetInstance()->GetData()[i]._type == Quantix::Core::Debugger::TypeLog::INFOS)
			ImGui::TextColored(ImVec4(52 / 255.f, 152 / 255.f, 219 / 255.f, 1), "Info: %s\n", Quantix::Core::Debugger::Logger::GetInstance()->GetData()[i]._message.c_str());
		else if (Quantix::Core::Debugger::Logger::GetInstance()->GetData()[i]._type == Quantix::Core::Debugger::TypeLog::WARNING)
			ImGui::TextColored(ImVec4(241 / 255.f, 196 / 255.f, 15 / 255.f, 1), "Warning: %s\n", Quantix::Core::Debugger::Logger::GetInstance()->GetData()[i]._message.c_str());
		else if (Quantix::Core::Debugger::Logger::GetInstance()->GetData()[i]._type == Quantix::Core::Debugger::TypeLog::ERROR)
			ImGui::TextColored(ImVec4(231 / 255.f, 76 / 255.f, 60 / 255.f, 1), "Error: %s\n", Quantix::Core::Debugger::Logger::GetInstance()->GetData()[i]._message.c_str());
		else if (Quantix::Core::Debugger::Logger::GetInstance()->GetData()[i]._type == Quantix::Core::Debugger::TypeLog::PROFILING)
			ImGui::TextColored(ImVec4(39 / 255.f, 174 / 255.f, 96 / 255.f, 1), "%s\n", Quantix::Core::Debugger::Logger::GetInstance()->GetData()[i]._message.c_str());
	}
}

void Editor::DrawConsole(QXstring name, ImGuiWindowFlags flags)
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

void Editor::DrawExplorer(QXstring name, ImGuiWindowFlags flags)
{
	_explorer.Update(_app->manager, name, flags);
}

void Editor::DrawInspector(QXstring name, ImGuiWindowFlags flags)
{
	ImGui::Begin(name.c_str(), NULL, flags);
	{
		if (_hierarchy.GetInspector() != nullptr)
			_hierarchy.GetInspector()->Update();
	}
	ImGui::End();
}