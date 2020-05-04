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

		if (!Try(_system->init(512, FMOD_INIT_3D_RIGHTHANDED, 0)))    // Initialize FMOD.
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

	QXbool SoundCore::Try(FMOD_RESULT result)
	{
		if (result != FMOD_OK)
		{
			printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
			return false;
		}

		return true;
	}

	QXuint SoundCore::AddListener()
	{
		for (QXuint index = 0; index < _listeners.size(); index++)
		{
			if (!_listeners[index])
			{
				_listeners[index] = true;
				return index;
			}
		}

		_listeners.push_back(true);
		return static_cast<QXuint>(_listeners.size()) - 1;

		//TODO : Maybe manage with _system->Set3DNumListener() and _system->Get3DNumListener() ?
	}

	void SoundCore::SuppListener(const QXuint ID)
	{
		_listeners[ID] = false;
	}

	#pragma endregion
}