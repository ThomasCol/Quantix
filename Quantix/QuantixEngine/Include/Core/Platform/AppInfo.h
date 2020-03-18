#ifndef __APPINFO_H__
#define __APPINFO_H__

#include "Core/Type.h"

namespace Quantix::Core::Platform
{
	struct AppInfo
	{
#pragma region Attributes

		QXuint		width;
		QXuint		height;

		QXdouble	deltaTime;
		QXdouble	currentTime;
		QXdouble	prevTime;

#pragma endregion
	};
}

#endif // __APPINFO_H__