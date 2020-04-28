#include "Resources/Sound.h"

#include "Core\SoundCore.h"

#include <stdio.h>
#include <fmod_errors.h>

namespace Quantix::Resources
{
	#pragma region Constructors & Destructor

	Sound::Sound(const char* path) : 
	_clip {nullptr}
	{
		Core::SoundCore::GetInstance()->Try(Core::SoundCore::GetInstance()->GetSystem()->createSound(path, FMOD_CREATESAMPLE, nullptr, &_clip));
	}

	Sound::Sound(const Sound& copy) noexcept :
	_clip {copy._clip}
	{}

	Sound::Sound(Sound&& copy) noexcept :
	_clip {copy._clip}
	{}

	Sound::~Sound()
	{
		_clip->release();
	}

	#pragma endregion

	#pragma region Methods

	#pragma region Accessors

	FMOD::Sound* Sound::GetClip()
	{
		return _clip;
	}

	QXstring Sound::GetName()
	{
		char*	name	{ nullptr };
		int		size	{ 256 };

		if (Core::SoundCore::GetInstance()->Try(_clip->getName(name, size)))
			return name;
		else
			return "Error : File not found";
	}

	QXstring Sound::GetType()
	{
		FMOD_SOUND_TYPE type;

		if (Core::SoundCore::GetInstance()->Try(_clip->getFormat(&type, nullptr, nullptr, nullptr)))
			return SortType(type);
		else
			return "Error : Type not found";
	}

	QXstring Sound::SortType(FMOD_SOUND_TYPE type)
	{
		switch (type)
		{
			case FMOD_SOUND_TYPE_AIFF:			return "AIFF";
			case FMOD_SOUND_TYPE_FLAC:			return "FLAC";
			case FMOD_SOUND_TYPE_MIDI:			return "MIDI";
			case FMOD_SOUND_TYPE_OGGVORBIS:		return "VORBIS OGG";
			case FMOD_SOUND_TYPE_WAV:			return "WAV";
			case FMOD_SOUND_TYPE_VORBIS:		return "VORBIS MP3";
			case FMOD_SOUND_TYPE_FADPCM:		return "PCM";
			case FMOD_SOUND_TYPE_UNKNOWN :		return "Unknown Type";
			default:							return "Type not managed";
		}
	}

	/*const unsigned int& Sound::GetSize()
	{

	}*/

	const QXuint Sound::GetTimeLength()
	{
		unsigned int time	{ 0 };

		if (Core::SoundCore::GetInstance()->Try(_clip->getLength(&time, FMOD_TIMEUNIT_MS)))
			return time;
		else
			return 0;
	}

	#pragma endregion

	bool Sound::Play()
	{
		return Core::SoundCore::GetInstance()->Try(Core::SoundCore::GetInstance()->GetSystem()->playSound(_clip, nullptr, false, nullptr));
	}

	#pragma endregion
}