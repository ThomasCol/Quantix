#pragma once

#include <queue>
#include <vector>
#include <future>
#include <mutex>
#include <functional>

#include "Task.h"
namespace Quantix::Core::Threading
{
	class TaskSystem
	{
	private:
		std::queue<std::function<void()>>	_tasks;

		size_t								_threadNumber;

		Task*								_threadPool;
		

		TaskSystem();
	public:
		TaskSystem(const TaskSystem& system) = delete;
		TaskSystem(TaskSystem&& system) = delete;
		~TaskSystem();

		static TaskSystem* GetInstance() noexcept
		{
			static TaskSystem ts;

			return &ts;
		}

		static void Destroy();
		static void Update();


		template<typename FuncType, typename ... Args>
		inline std::future<typename std::result_of<FuncType(Args...)>::type> AddTaskReturn(FuncType&& func, Args&& ... vars);

		template<typename FuncType, typename ... Args>
		inline void AddTask(FuncType&& func, Args&& ... vars);
	};

	template<typename FuncType, typename ... Args>
	inline std::future<typename std::result_of<FuncType(Args...)>::type> TaskSystem::AddTaskReturn(FuncType&& func, Args&& ... vars)
	{
		using return_type = typename std::result_of<FuncType(Args...)>::type;

		auto task = std::make_shared< std::packaged_task<return_type()>>
			(std::bind(std::forward<FuncType>(func), std::forward<Args>(vars)...));

		std::future<return_type> res = task->get_future();

		_tasks.emplace([task] { (*task)(); });

		return res;

	}

	template<typename FuncType, typename ... Args>
	inline void TaskSystem::AddTask(FuncType&& func, Args&& ... vars)
	{
		_tasks.emplace(std::bind(std::forward<FuncType>(func), std::forward<Args>(vars)...));
	}
}