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

	void Profiler::StartProfiling(const QXstring& type)
	{
		if (!_activate)
		{
			_profiling = BEGIN_PROFILING;
			_activate = true;
		}
		_infoProfiling.insert(std::make_pair(type, Info{type + "\n", glfwGetTime(), 0.f, currId, true}));

		currId++;
	}

	void Profiler::SetMessage(const QXstring& type, const QXstring& msg)
	{
		if (_infoProfiling[type].activate)
			_infoProfiling[type].msg += msg;
	}

	void Profiler::StopProfiling(const QXstring& type)
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

	void Profiler::SetProfiling()
	{
		typedef std::pair<QXstring, Info> pair;
		// create an empty vector of pairs
		std::vector<pair> vec;

		// copy key-value pairs from the map to the vector
		std::copy(_infoProfiling.begin(), _infoProfiling.end(),	std::back_inserter<std::vector<pair>>(vec));

		// sort the vector by increasing order of its pair's second value
		// if second value are equal, order by the pair's first value
		std::sort(vec.begin(), vec.end(), [](const pair& l, const pair& r) 
		{
			if (l.second.id != r.second.id)
				return l.second.id < r.second.id;

			return l.first < r.first;
		});

		for (auto const& pair : vec)
		{
			_profiling += pair.second.msg;
			std::ostringstream streamObj;

			// Set Fixed -Point Notation
			streamObj << std::fixed;
			// Set precision to 2 digits
			streamObj << std::setprecision(2);

			streamObj << pair.second.timer;
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