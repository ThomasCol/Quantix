#include "Core/Components/SoundEmitter.h"

#include <Vec3.h>

#include "Core\SoundCore.h"
#include "Core\DataStructure\GameObject3D.h"

namespace Quantix::Core::Components
{
	#pragma region Constructors & Destructor

	SoundEmitter::SoundEmitter() :
	_sound {nullptr},
	_channel {nullptr},
	_soundMode {Resources::ESoundMode::QX_2D},
	_loop {false},
	_playOnAwake {false}
	{}

	SoundEmitter::SoundEmitter(Resources::Sound* sound) noexcept :
	_sound { sound },
	_channel { nullptr },
	_soundMode { Resources::ESoundMode::QX_2D },
	_loop { false },
	_playOnAwake { false }
	{}

	SoundEmitter::SoundEmitter(const SoundEmitter& copy) noexcept :
	_sound { copy._sound },
	_channel { copy._channel },
	_soundMode {copy._soundMode},
	_loop { copy._loop },
	_playOnAwake { copy._playOnAwake }
	{}

	SoundEmitter::SoundEmitter(SoundEmitter&& copy) noexcept :
	_sound { std::move(copy._sound) },
	_channel { std::move(copy._channel) },
	_soundMode { std::move(copy._soundMode) },
	_loop { std::move(copy._loop) },
	_playOnAwake { std::move(copy._playOnAwake) }
	{}

	SoundEmitter::~SoundEmitter()
	{
		delete _sound;
		delete _channel;
	}

	#pragma endregion

	#pragma region Methods

	void SoundEmitter::UpdateAttributes()
	{
		if (_sound->Is3D())
		{
			DataStructure::GameObject3D* go = static_cast<DataStructure::GameObject3D*>(_object);
			FMOD_VECTOR pos{ go->GetTransform()->GetPosition().x, go->GetTransform()->GetPosition().y, go->GetTransform()->GetPosition().z };
			Core::SoundCore::GetInstance()->Try(_channel->set3DAttributes(&pos, nullptr));
		}
	}

	SoundEmitter* SoundEmitter::Copy() const
	{
		return new SoundEmitter(*this);
	}

	const QXbool SoundEmitter::PlaySound()
	{
		return _sound->Play(_channel);
	}

	const QXbool SoundEmitter::SetSoundMode(Resources::ESoundMode mode)
	{
		FMOD_MODE fmode;
		switch (mode)
		{
			case Resources::ESoundMode::QX_2D:	fmode = FMOD_2D;
			case Resources::ESoundMode::QX_3D:	fmode = FMOD_3D;
			default:							fmode = FMOD_DEFAULT;
		}

		_soundMode = mode;
		return _sound->ChangeMode(fmode);
	}

	#pragma endregion
}