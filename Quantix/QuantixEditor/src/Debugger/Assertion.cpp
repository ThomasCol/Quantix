#include "Assertion.h"
#include "Logger.h"

#include <iostream>

namespace Quantix::Core::Debugger
{
	void	StaticAssert(QXbool condition, QXstring file, QXint line)
	{
		if (!condition)
		{
			QXstring	time = __TIME__;

			QXstring log{ "[Static Assert]  " + time + "\n\t> in file " + file +
			", line " + std::to_string(line) + ".\n" };

			std::cout << "Static Assert" << std::endl;

			Logger::GetInstance()->SetError(log);

			exit(0);
		}
	}

	void	Assert(QXbool condition, QXstring file, QXint line)
	{
		if (!condition)
		{

			QXstring log{ "[Assert]\n\t> in file " + file +
			", line " + std::to_string(line) + ".\n" };

			std::cout << "Assert" << std::endl;

			Logger::GetInstance()->SetError(log);
		}
	}
}