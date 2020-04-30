#pragma once

#include <thread>
#include <atomic>

namespace Quantix::Core::Threading
{
	struct Task
	{
		Task() = default;
		Task(const Task& task) :
			done{ task.done.load() }
		{};

		std::thread			thread;
		std::atomic_bool	done = true;
	};
}