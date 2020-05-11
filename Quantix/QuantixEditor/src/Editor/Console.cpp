#include "Console.h"
#include <Core/Profiler/Profiler.h>

Console::Console() :
	_sizeLog{ 0 }
{
	_showTypeLog.push_back(QX_TRUE);
	_showTypeLog.push_back(QX_TRUE);
	_showTypeLog.push_back(QX_TRUE);
}

Console::~Console()
{
}

void Console::Init(Quantix::Core::Platform::Application* app)
{
	_imgTypeLog.push_back(app->manager.CreateTexture("Other/IconEditor/Simulation/info.png"));
	_imgTypeLog.push_back(app->manager.CreateTexture("Other/IconEditor/Simulation/warning.png"));
	_imgTypeLog.push_back(app->manager.CreateTexture("Other/IconEditor/Simulation/error.png"));
}

void Console::PrintLog()
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

void Console::ConsoleUI()
{
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(192 / 255.f, 57 / 255.f, 43 / 255.f, 1.f));
	if (ImGui::Button("Clear", ImVec2(75, 0)))
		Quantix::Core::Debugger::Logger::GetInstance()->ClearMessage();
	ImGui::PopStyleColor();
	ImGui::SameLine();
	ImGui::Dummy(ImVec2(20, 20));
	for (QXuint i = 0; i < _showTypeLog.size(); i++)
	{
		ImGui::SameLine();
		ImGui::BeginGroup();
		if (ImGui::ImageButton((ImTextureID)_imgTypeLog[i]->GetId(), ImVec2(20, 20), ImVec2(0, 1), ImVec2(1, 0)))
			_showTypeLog[i] = !_showTypeLog[i];
		ImGui::SameLine();
		ImGui::Text("%d", Quantix::Core::Debugger::Logger::GetInstance()->GetMessage()[i]);
		ImGui::EndGroup();
	}
}

void Console::Update(const QXstring& name, ImGuiWindowFlags flags)
{
	ImGui::Begin(name.c_str(), NULL, flags);
	{
		static QXbool ShowDemoWindow = QX_FALSE;
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
