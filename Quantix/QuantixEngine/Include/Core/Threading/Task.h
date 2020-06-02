#pragma once

#include <thread>
#include <atomic>

namespace Quantix::Core::Threading
{
	struct Task
	{
		#pragma region Constructors

		/**
		 * @brief Construct a new Task object
		 * 
		 */
		Task() = default;

		/**
		 * @brief Construct a new Task object
		 * 
		 * @param task Task to copy
		 */
		Task(const Task& task) noexcept :
			done{ task.done.load() }
		{};

		#pragma endregion

		#pragma region Attributes

		std::thread			thread;
		std::atomic_bool	done = true;

		#pragma endregion
	};
}