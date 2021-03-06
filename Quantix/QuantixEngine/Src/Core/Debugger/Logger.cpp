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
	}

	void Logger::SetMessage(TypeLog type, const QXstring& message)
	{
		switch (type)
		{
			case Quantix::Core::Debugger::TypeLog::INFOS: _instance->SetInfo(message); break;
			case Quantix::Core::Debugger::TypeLog::WARNING: _instance->SetWarning(message);  break;
			case Quantix::Core::Debugger::TypeLog::ERROR: _instance->SetError(message); break;
			case Quantix::Core::Debugger::TypeLog::PROFILING: _instance->SetProfiling(message); break;
			default: break;
		}
	}

	void Logger::SetInfo(const QXstring& msg)
	{
		Data d = { std::string("[INFOS] ") + __TIME__ + std::string(": ") + msg, TypeLog::INFOS };
		_data.push_back(d);
		_nbMessage[0] += 1;
	}

	void Logger::SetWarning(const QXstring& msg)
	{
		Data d = { std::string("[WARNING] ") + __TIME__ + std::string(": ") + msg, TypeLog::WARNING };
		_data.push_back(d);
		_nbMessage[1] += 1;
	}

	void Logger::SetError(const QXstring& msg)
	{
		Data d = { std::string("[ERROR] ") + __TIME__ + std::string(": ") + msg, TypeLog::ERROR };
		_data.push_back(d);
		_nbMessage[2] += 1;
	}

	void Logger::SetProfiling(const QXstring& msg)
	{
		Data d = { __TIME__ + std::string(":\n") + msg, TypeLog::PROFILING };
		_data.push_back(d);
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

	void Logger::ClearMessage()
	{
		_data.clear();
		for (QXuint i = 0; i < _nbMessage.size(); i++)
			_nbMessage[i] = 0;
	}

	Logger* Logger::GetInstance()
	{
		if (!_instance)
		{
			_instance = new Logger();
			_instance->_nbMessage.push_back(0);
			_instance->_nbMessage.push_back(0);
			_instance->_nbMessage.push_back(0);
		}
		return _instance;
	}
}