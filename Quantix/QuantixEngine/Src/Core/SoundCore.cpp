#include "Core/SoundCore.h"

#include <fmod_errors.h>
#include <stdio.h>

namespace Quantix::Core
{
	SoundCore* SoundCore::_instance = nullptr;

	#pragma region Constructors & Destructors

	SoundCore::SoundCore() :
	_system {nullptr}
	{
		if (!Try(FMOD::System_Create(&_system))) // Create the main system object.
			return;

		if (!Try(_system->init(512, FMOD_INIT_NORMAL, 0)))    // Initialize FMOD.
			return;
	}

	SoundCore::~SoundCore()
	{
		_system->release();
	}

	#pragma endregion

	#pragma region Methods

	void SoundCore::Update()
	{
		_system->update();
	}

	bool SoundCore::Try(FMOD_RESULT result)
	{
		if (result != FMOD_OK)
		{
			printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
			return false;
		}

		return true;
	}

	#pragma endregion
}