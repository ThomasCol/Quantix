#include "Core/Threading/TaskSystem.hpp"

#include "Core/Debugger/Logger.h"

namespace Quantix::Core::Threading
{
	TaskSystem::TaskSystem() :
		_threadNumber{ std::thread::hardware_concurrency() }
	{
		_threadPool = new Task[_threadNumber];
	}

	TaskSystem::~TaskSystem()
	{
	}

	void TaskSystem::Destroy()
	{
		TaskSystem* syst = GetInstance();
		for (size_t i = 0; i < syst->_threadNumber; i++)
		{
			if (syst->_threadPool[i].thread.joinable())
				syst->_threadPool[i].thread.join();
		}
		delete[] syst->_threadPool;
	}

	void TaskSystem::Update()
	{
		TaskSystem* tasks = GetInstance();
		if (tasks->_tasks.empty())
			return;

		for (size_t i = 0; i < tasks->_threadNumber; i++)
		{
			if (tasks->_threadPool[i].done.load())
			{
				if (tasks->_threadPool[i].thread.joinable())
					tasks->_threadPool[i].thread.join();

				Task* task = &(tasks->_threadPool[i]);
				task->done.store(false);
				std::function<void()> func = tasks->_tasks.front();

				if (!func)
					return;
				task->thread = std::thread([func, task]
					{
						try
						{
							if (func)
								func();
						}
						catch (std::exception e)
						{
							LOG(WARNING, e.what());
						}
						task->done.store(true);
					});
				tasks->_tasks.pop();
				if (tasks->_tasks.empty())
					return;
			}
		}
	}
}