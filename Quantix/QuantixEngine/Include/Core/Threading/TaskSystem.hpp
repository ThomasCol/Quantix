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
		#pragma region Attributes

		std::queue<std::function<void()>>	_tasks;

		size_t								_threadNumber;

		Task*								_threadPool;
		
		#pragma endregion

		#pragma region Constructors

		/**
		 * @brief Construct a new Task System object
		 * 
		 */
		TaskSystem() noexcept;

		#pragma endregion

	public:
		#pragma region Constructors

		/**
		 * @brief Construct a new Task System object (DELETED)
		 * 
		 * @param system system to copy
		 */
		TaskSystem(const TaskSystem& system) = delete;

		/**
		 * @brief Construct a new Task System object (DELETED)
		 * 
		 * @param system system to move
		 */
		TaskSystem(TaskSystem&& system) = delete;

		/**
		 * @brief Destroy the Task System object
		 * 
		 */
		~TaskSystem() noexcept;

		#pragma endregion

		#pragma region Accessors

		/**
		 * @brief Get the Instance object
		 * 
		 * @return TaskSystem* Instance of task system
		 */
		static TaskSystem* GetInstance() noexcept
		{
			static TaskSystem ts;

			return &ts;
		}

		#pragma endregion

		#pragma region Functions

		/**
		 * @brief Destroy system
		 * 
		 */
		static void Destroy() noexcept;

		/**
		 * @brief Update task system
		 * 
		 */
		static void Update() noexcept;


		/**
		 * @brief Add a task to the pool and allow return
		 * 
		 * @tparam FuncType Function type
		 * @tparam Args arguments of the function
		 * @param func Function to add
		 * @param vars variables of the functions
		 * @return std::future<typename std::result_of<FuncType(Args...)>::type> std::future of your function return
		 */
		template<typename FuncType, typename ... Args>
		inline std::future<typename std::result_of<FuncType(Args...)>::type> AddTaskReturn(FuncType&& func, Args&& ... vars) noexcept;

		/**
		 * @brief Add a task to the pool
		 * 
		 * @tparam FuncType Function type
		 * @tparam Args arguments of the function
		 * @param func Function to add
		 * @param vars variables of the functions
		 */
		template<typename FuncType, typename ... Args>
		inline void AddTask(FuncType&& func, Args&& ... vars) noexcept;

		#pragma endregion
	};

	template<typename FuncType, typename ... Args>
	inline std::future<typename std::result_of<FuncType(Args...)>::type> TaskSystem::AddTaskReturn(FuncType&& func, Args&& ... vars) noexcept
	{
		using return_type = typename std::result_of<FuncType(Args...)>::type;

		auto task = std::make_shared< std::packaged_task<return_type()>>
			(std::bind(std::forward<FuncType>(func), std::forward<Args>(vars)...));

		std::future<return_type> res = task->get_future();

		_tasks.emplace([task] { (*task)(); });

		return res;

	}

	template<typename FuncType, typename ... Args>
	inline void TaskSystem::AddTask(FuncType&& func, Args&& ... vars) noexcept
	{
		_tasks.emplace(std::bind(std::forward<FuncType>(func), std::forward<Args>(vars)...));
	}
}