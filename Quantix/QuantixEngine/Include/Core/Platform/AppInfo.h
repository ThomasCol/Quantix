#ifndef __APPINFO_H__
#define __APPINFO_H__

#include <Type.h>
#include <Mat4.h>
#include "Core/DLLHeader.h"

namespace Quantix::Core::Platform
{
	struct QUANTIX_API AppInfo
	{
#pragma region Attributes

		QXuint			width;
		QXuint			height;

		QXdouble		deltaTime;
		QXdouble		currentTime;
		QXdouble		prevTime;

		Math::QXmat4	proj;

#pragma endregion
	};
}

#endif // __APPINFO_H__