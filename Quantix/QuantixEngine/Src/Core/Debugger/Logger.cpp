//#include <imgui.h>
#include <ctime>
#include <chrono>

#include "Core/Debugger/Logger.h"

static void findAndReplaceAll(QXstring& data, QXstring toSearch, QXstring replaceStr)
{
	// Get the first occurrence
	size_t pos = data.find(toSearch);

	// Repeat till end is reached
	while (pos != QXstring::npos)
	{
		// Replace this occurrence of Sub String
		data.replace(pos, toSearch.size(), replaceStr);
		// Get the next occurrence from the current position
		pos = data.find(toSearch, pos + replaceStr.size());
	}
}

namespace Quantix::Core::Debugger
{
	Logger* Logger::_instance = nullptr;

	Logger::Logger()
	{
	}

	Logger::~Logger()
	{
		QXstring cmd = "mkdir " + fs::current_path().string() + "\\Log";
		std::cout << "Create Folder: " << cmd << std::endl;
		system(cmd.c_str());

		QXstring date = __DATE__;
		findAndReplaceAll(date, " ", "_");
		QXstring time = __TIME__;
		findAndReplaceAll(time, ":", "_");

		QXstring fileName = fs::current_path().string() + "\\Log\\tmp_" + date + "_" + time + ".log";
		std::cout << "Log File: " << fileName << std::endl;

		std::ofstream myfile;
		myfile.open(fileName.c_str());
		for (QXuint i{ 0 }; i < _data.size(); i++)
			myfile << _data[i]._message + "\n";
		myfile.close();
		//delete m_instance;
	}

	void Logger::SetInfos(const QXstring& msg)
	{
		Data d = { std::string("[INFOS] ") + __TIME__ + std::string(": ") + msg, TypeLog::INFOS };
		_data.push_back(d);
	}

	void Logger::SetWarning(const QXstring& msg)
	{
		Data d = { std::string("[WARNING] ") + __TIME__ + std::string(": ") + msg, TypeLog::WARNING };
		_data.push_back(d);
	}

	void Logger::SetError(const QXstring& msg)
	{
		Data d = { std::string("[ERROR] ") + __TIME__ + std::string(": ") + msg, TypeLog::ERROR };
		_data.push_back(d);
	}

	void Logger::SetProfiling(const QXstring& msg)
	{
		Data d = { __TIME__ + std::string(":\n") + msg, TypeLog::PROFILING };
		_data.push_back(d);
	}

	void Logger::PrintLog()
	{
		/*	ImGuiStyle& style = ImGui::GetStyle();
			for (unsigned int i = 0; i < _data.size(); i++)
			{
				if (_data[i]._type == TypeLog::INFOS)
					ImGui::TextColored(ImVec4(52 / 255.f, 152 / 255.f, 219 / 255.f, 1), "Info: %s\n", _data[i]._message.c_str());
				else if (_data[i]._type == TypeLog::WARNING)
					ImGui::TextColored(ImVec4(241 / 255.f, 196 / 255.f, 15 / 255.f, 1), "Warning: %s\n", _data[i]._message.c_str());
				else if (_data[i]._type == TypeLog::ERROR)
					ImGui::TextColored(ImVec4(231 / 255.f, 76 / 255.f, 60 / 255.f, 1), "Error: %s\n", _data[i]._message.c_str());
				else if (_data[i]._type == TypeLog::PROFILING)
					ImGui::TextColored(ImVec4(39 / 255.f, 174 / 255.f, 96 / 255.f, 1), "%s\n", _data[i]._message.c_str());
			}*/
	}

	void Logger::SendMessage(TypeLog type, QXstring message)
	{
		switch (type)
		{
		case Quantix::Core::Debugger::TypeLog::INFOS: _instance->SetInfos(message); break;
		case Quantix::Core::Debugger::TypeLog::WARNING:  _instance->SetWarning(message); break;
		case Quantix::Core::Debugger::TypeLog::ERROR: _instance->SetError(message); break;

		default:
			break;
		}
	}

	void Logger::CloseLogger()
	{
		QXstring cmd = "mkdir " + fs::current_path().string() + "\\Log";
		std::cout << "Create Folder: " << cmd << std::endl;
		system(cmd.c_str());

		QXstring date = __DATE__;
		findAndReplaceAll(date, " ", "_");
		QXstring time = __TIME__;
		findAndReplaceAll(time, ":", "_");

		QXstring fileName = fs::current_path().string() + "\\Log\\tmp_" + date + "_" + time + ".log";
		std::cout << "Log File: " << fileName << std::endl;

		std::ofstream myfile;
		myfile.open(fileName.c_str());
		for (QXuint i{ 0 }; i < _data.size(); i++)
				myfile << _data[i]._message + "\n";
		myfile.close();
	}

	Logger* Logger::GetInstance()
	{
		if (!_instance)
			_instance = new Logger();
		return _instance;
	}
}