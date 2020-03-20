#include "Core/Profiler/Profiler.h"
#include <sstream>
#include <iomanip>
#include <set>
#include <algorithm>
#include <functional>

namespace Quantix::Core::Profiling
{
	static QXint currId = 0;

	Profiler* Profiler::_instance = nullptr;

	Profiler::Profiler()
	{
	}

	Profiler::~Profiler()
	{
	}

	void	Profiler::FrameCounter()
	{
		static QXdouble current_time = 0;
		static QXdouble last_time = 0;
		static QXint n = 0;
		_frameRate = n;

		n++;
		current_time = glfwGetTime();

		if ((current_time - last_time) >= 1)
		{
			// nombre de frames par seconde
			_frameRate = n;
			n = 0;
			last_time = current_time;
		}
	}

	int	Profiler::GetFrameCounter()
	{
		return _frameRate;
	}

	void Profiler::StartProfiling(QXstring type)
	{
		if (!_activate)
		{
			_profiling = BEGIN_PROFILING;
			_activate = true;
		}
		_infoProfiling.insert(std::make_pair(type, Info{type + "\n", glfwGetTime(), 0.f, currId, true}));

		currId++;
	}

	void Profiler::SetMessage(QXstring type, QXstring msg)
	{
		if (_infoProfiling[type].activate)
			_infoProfiling[type].msg += msg;
	}

	void Profiler::StopProfiling(QXstring type)
	{
		_infoProfiling[type].activate = false;
		for (std::map<QXstring, Info>::iterator it = _infoProfiling.begin(); it != _infoProfiling.end(); ++it)
			if (it->second.activate)
			{
				it->second.timer = glfwGetTime() - it->second.beginTime;
				return;
			}
		_activate = false;
		currId = 0;

		SetProfiling();

		QXstring fps = "FPS: " + std::to_string(GetFrameCounter());

		_profiling += fps;
		_profiling += "\n\n" + QXstring(END_PROFILING);

		Quantix::Core::Debugger::Logger::GetInstance()->SetProfiling(_profiling);
		_profiling = "";
		_infoProfiling.clear();
	}

	void Profiler::Update(QXfloat deltaTime)
	{
		for (std::map<QXstring, Info>::iterator it = _infoProfiling.begin(); it != _infoProfiling.end(); ++it)
			if (it->second.activate)
				it->second.timer += _info.deltaTime;
	}

	void Profiler::SetProfiling()
	{
		typedef std::function<bool(std::pair<QXstring, Info>, std::pair<QXstring, Info>)> Comparator;

		// Defining a lambda function to compare two pairs. It will compare two pairs using second field
		Comparator compFunctor =
			[](std::pair<QXstring, Info> elem1, std::pair<QXstring, Info> elem2)
		{
			return elem1.second.id > elem2.second.id;
		};

		// Declaring a set that will store the pairs using above comparision logic
		std::set<std::pair<QXstring, Info>, Comparator> profilingInfo(
			_infoProfiling.begin(), _infoProfiling.end(), compFunctor);

		for (std::pair<QXstring, Info> it : _infoProfiling)
		{
			_profiling += it.second.msg;
			std::ostringstream streamObj;
			// Set Fixed -Point Notation
			streamObj << std::fixed;

			// Set precision to 2 digits
			streamObj << std::setprecision(2);

			streamObj << it.second.timer;
			QXstring time = "**** Time to process ****: " + streamObj.str() + "seconds\n\n";
			_profiling += time;
		}
	}

	Profiler* Profiler::GetInstance()
	{
		if (!_instance)
			_instance = new Profiler();
		return _instance;
	}
}