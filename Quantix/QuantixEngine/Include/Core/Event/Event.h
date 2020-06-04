#ifndef __EVENT_H__
#define __EVENT_H__

#include <iostream>
#include <functional>
#include <future>
#include <vector>
#include "Core/DLLHeader.h"
#include <Type.h>

namespace Quantix::Core::Event
{

	/* Usage:
	** To subscribe with a simple function
	**		event += function;
	**
	** To subscribe with a class method
	**		event += std::bind(&className::methodName, &object, ARGx);
	**															 ^=> none if no arg
	**
	*/

	template<typename... Args>
	class QUANTIX_API Event
	{
		std::vector<std::function<void(Args...)>> _functions;

	public:
		Event() = default;
		Event(const Event<Args...>& src) = default;
		Event(Event<Args...>&& src) = default;
		~Event() = default;

		Event& operator=(const Event& other) = default;
		Event& operator=(Event&& other) = default;

		inline Event& operator+=(std::function<void(Args...)> func)
		{
			_functions.push_back(func);
			return *this;
		}

		template<typename FuncType, typename ... Args>
		void AddFunc(FuncType&& func, Args&& ... vars) noexcept
		{
			_functions.push_back(std::bind(std::forward<FuncType>(func), std::forward<Args>(vars)...));
		}

		inline Event& operator-=(std::function<void(Args...)> func)
		{
			for (auto it = _functions.begin(); it != _functions.end(); ++it)
				if (func.target_type() == (*it).target_type())
				{
					_functions.erase(it);
					return *this;
				}

			return *this;
		}

		template<typename ... Args>
		void Raise(Args ... vars) noexcept
		{
			for (auto it{ _functions.begin() }; it != _functions.end();)
			{
				if (*it != nullptr)
					(*it++)(vars...);
			}
		}
	};
}
#endif
