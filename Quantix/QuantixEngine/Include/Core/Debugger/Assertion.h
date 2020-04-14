#pragma once

#include <string>
#include <exception>
#include "Core/Type.h"

namespace Quantix::Core::Debugger
{
	#pragma region Functions
	/**
	 * @brief Static Assert break program
	 * 
	 * @param condition 
	 * @param file 
	 * @param line 
	 */
	void QUANTIX_API 	StaticAssert(QXbool condition, QXstring file, QXint line);

	/**
	 * @brief Assert send an alert
	 * 
	 * @param condition 
	 * @param file 
	 * @param line 
	 */
	void QUANTIX_API	Assert(QXbool condition, QXstring file, QXint line);
	#pragma endregion Functions
}

/* Macro to deactivate asserts */
#ifdef NDEBUG
#define ASSERT(condition) ((void)0)
#define STATICASSERT(condition) throw std::string("fail")
/* Macro to call asserts */
#else
#define ASSERT(condition)\
	Quantix::Core::Debugger::Assert(condition, __FILE__, __LINE__)
#define STATICASSERT(condition)\
	Quantix::Core::Debugger::StaticAssert(condition, __FILE__, __LINE__)
#endif
