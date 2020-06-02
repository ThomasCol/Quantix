#include "Core/Components/SoundEmitter.h"

#include <Vec3.h>

#include "Core\SoundCore.h"
#include "Core\DataStructure\GameObject3D.h"

RTTR_PLUGIN_REGISTRATION
{
	rttr::registration::class_<Quantix::Core::Components::SoundEmitter>("SoundEmitter")
	.constructor<>()
	.constructor<Quantix::Resources::Sound*>()
	.constructor<const Quantix::Core::Components::SoundEmitter&>()
	.constructor<Quantix::Core::Components::SoundEmitter&&>()
	.property("Sound", &Quantix::Core::Components::SoundEmitter::_sound)
	.property("Channel", &Quantix::Core::Components::SoundEmitter::_channel)
	.property("Mode", &Quantix::Core::Components::SoundEmitter::GetDimensionalSoundMode, &Quantix::Core::Components::SoundEmitter::SetDimensionalSoundMode)
	.property("Volume", &Quantix::Core::Components::SoundEmitter::GetVolume, &Quantix::Core::Components::SoundEmitter::SetVolume)
	.property("Loop", &Quantix::Core::Components::SoundEmitter::IsLooping, &Quantix::Core::Components::SoundEmitter::SetLoop)
	.property("On Awake", &Quantix::Core::Components::SoundEmitter::_playOnAwake)
	.method("AttributesEmitter", &Quantix::Core::Components::SoundEmitter::UpdateAttributes)
	.method("PlaySound", &Quantix::Core::Components::SoundEmitter::PlaySound);
}

namespace Quantix::Core::Components
{
	#pragma region Constructors & Destructor

	SoundEmitter::SoundEmitter() :
	_sound {nullptr},
	_channel {nullptr},
	_volume { 1.f },
	_soundMode{ QX_SOUNDMODE_DEFAULT },
	_dimensionalMode { Resources::ESoundMode::QX_2D },
	_loop {false},
	_playOnAwake {false}
	{}

	SoundEmitter::SoundEmitter(Resources::Sound* sound) noexcept :
	_sound { sound },
	_channel { nullptr },
	_soundMode { QX_SOUNDMODE_DEFAULT },
	_dimensionalMode{ Resources::ESoundMode::QX_2D },
	_volume{ 1.f },
	_loop { false },
	_playOnAwake { false }
	{}

	SoundEmitter::SoundEmitter(const SoundEmitter& copy) noexcept :
	_sound { copy._sound },
	_channel { copy._channel },
	_soundMode {copy._soundMode},
	_dimensionalMode{ copy._dimensionalMode },
	_volume{ copy._volume },
	_loop { copy._loop },
	_playOnAwake { copy._playOnAwake }
	{}

	SoundEmitter::SoundEmitter(SoundEmitter&& copy) noexcept :
	_sound { std::move(copy._sound) },
	_channel { std::move(copy._channel) },
	_soundMode { std::move(copy._soundMode) },
	_dimensionalMode{ std::move(copy._dimensionalMode) },
	_volume{ std::move(copy._volume) },
	_loop { std::move(copy._loop) },
	_playOnAwake { std::move(copy._playOnAwake) }
	{}

	SoundEmitter::~SoundEmitter()
	{
		_channel->stop();
		_channel->release();
	}

	#pragma endregion

	#pragma region Methods

	void SoundEmitter::UpdateAttributes()
	{
		if (_sound->Is3D())
		{
			Quantix::Core::DataStructure::GameObject3D* go = static_cast<Quantix::Core::DataStructure::GameObject3D*>(_object);
			FMOD_VECTOR pos{ go->GetTransform()->GetPosition().x, go->GetTransform()->GetPosition().y, go->GetTransform()->GetPosition().z };
			Core::SoundCore::GetInstance()->Try(_channel->set3DAttributes(&pos, nullptr));
		}
	}

	SoundEmitter* SoundEmitter::Copy() const
	{
		return new SoundEmitter(*this);
	}

	void SoundEmitter::Init(Quantix::Core::DataStructure::GameComponent* object)
	{
		_object = object;
		_sound = nullptr;
		_channel = nullptr;
		_soundMode = QX_SOUNDMODE_DEFAULT;
		_dimensionalMode = Resources::ESoundMode::QX_2D;
		_loop = false;
		_playOnAwake = false;
	}

	const QXbool SoundEmitter::PlaySound()
	{
		StopSound();

		return _sound->Play(_channel);
	}

	const QXbool SoundEmitter::PauseSound()
	{
		if (_channel)
			_channel->setPaused(QX_TRUE);

		return _sound->Pause();
	}

	const QXbool SoundEmitter::UnPauseSound()
	{
		if (_channel)
			_channel->setPaused(QX_FALSE);

		return _sound->UnPause();
	}

	const QXbool SoundEmitter::StopSound()
	{
		if (_channel)
			_channel->stop();

		return _sound->Stop();
	}

	void SoundEmitter::SetDimensionalSoundMode(const Resources::ESoundMode& mode) //Enumerator to handle the insector choice wether the sound is in 2d or 3D
	{
		QXuint	soundMode = QX_SOUNDMODE_DEFAULT;

		if (mode == Resources::ESoundMode::QX_2D)
		{
			DeleteSoundMode(QX_SOUNDMODE_3D);
			soundMode = QX_SOUNDMODE_2D;
		}
		else if (mode == Resources::ESoundMode::QX_3D)
		{
			DeleteSoundMode(QX_SOUNDMODE_2D);
			soundMode = QX_SOUNDMODE_3D;
		}

		_dimensionalMode = mode;
		_soundMode = soundMode;
		AddSoundMode(_soundMode);
	}

	void SoundEmitter::AddSoundMode(const QXSoundMode& mode) //Add a mode using the bitflag system
	{
		_soundMode |= mode;
		
		if (_channel)
			Core::SoundCore::GetInstance()->Try(_channel->setMode(_soundMode));
		
		_sound->ChangeMode(_soundMode);
	}

	void SoundEmitter::DeleteSoundMode(const QXSoundMode& mode) //Delete a mode using the bitflag system
	{
		_soundMode &= ~mode;
		
		if (_channel)
			Core::SoundCore::GetInstance()->Try(_channel->setMode(_soundMode));
		
		_sound->ChangeMode(_soundMode);
	}

	#pragma endregion
}