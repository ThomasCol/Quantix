#include "Resources/Sound.h"

#include "Core\SoundCore.h"

#include <stdio.h>
#include <iostream>

RTTR_PLUGIN_REGISTRATION
{
	rttr::registration::class_<Quantix::Resources::Sound>("Sound")
	.constructor<const char*>()
	.constructor<const Quantix::Resources::Sound&>()
	.constructor<Quantix::Resources::Sound&&>()
	.enumeration<Quantix::Resources::ESoundMode>("Sound Type")
					 (rttr::value("QX_2D", Quantix::Resources::ESoundMode::QX_2D),
					 rttr::value("QX_3D", Quantix::Resources::ESoundMode::QX_3D))
	.method("GetPath", &Quantix::Resources::Sound::GetPath);
}

namespace Quantix::Resources
{

	#pragma region Constructors & Destructor

	Sound::Sound(const char* path) : 
		_clip{ nullptr },
		_channel {nullptr},
		_path {path}
	{
		Core::SoundCore::GetInstance()->Try(Core::SoundCore::GetInstance()->GetSystem()->createSound(path, FMOD_DEFAULT, nullptr, &_clip));
	}

	Sound::Sound(const Sound& copy) noexcept :
	_clip {copy._clip},
	_channel { copy._channel }
	{}

	Sound::Sound(Sound&& copy) noexcept :
	_clip { std::move(copy._clip) },
	_channel { std::move(copy._channel) }
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

	const QXfloat Sound::GetVolume()
	{
		QXfloat	volume	{ 0.f };
		if (this && _channel)
			if (Core::SoundCore::GetInstance()->Try(_channel->getVolume(&volume)))
				return volume;
		return 0;
	}

	void Sound::SetVolume(QXfloat newVolume)
	{
		if (this && _channel)
			Core::SoundCore::GetInstance()->Try(_channel->setVolume(newVolume));
	}

	#pragma endregion

	const QXbool Sound::Play()
	{
		return Core::SoundCore::GetInstance()->Try(Core::SoundCore::GetInstance()->GetSystem()->playSound(_clip, nullptr, false, &_channel));
	}

	const QXbool Sound::Play(FMOD::ChannelGroup* channel)
	{
		if (this != nullptr && _clip)
			return Core::SoundCore::GetInstance()->Try(Core::SoundCore::GetInstance()->GetSystem()->playSound(_clip, channel, false, &_channel));
		return false;
	}

	const QXbool Sound::Pause(FMOD::ChannelGroup* channel)
	{
		if (this != nullptr && _clip)
			return Core::SoundCore::GetInstance()->Try(Core::SoundCore::GetInstance()->GetSystem()->playSound(_clip, channel, true, nullptr));
		return false;
	}

	const QXbool Sound::Is3D()
	{
		if (this && _clip)
		{
			FMOD_MODE	clipMode;

			if (Core::SoundCore::GetInstance()->Try(_clip->getMode(&clipMode)))
				return ((clipMode & FMOD_3D) == FMOD_3D);
		}

		return false;
	}

	const QXbool Sound::ChangeMode(FMOD_MODE mode)
	{
		if (this)
			return (Core::SoundCore::GetInstance()->Try(_clip->setMode(mode)));
		else
			return false;
	}

	#pragma endregion
}