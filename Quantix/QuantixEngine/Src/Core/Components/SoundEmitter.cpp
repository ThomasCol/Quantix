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
	.property("Mode", &Quantix::Core::Components::SoundEmitter::GetSoundMode, &Quantix::Core::Components::SoundEmitter::SetSoundMode)
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
	_soundMode{ QX_SOUNDMODE_DEFAULT },
	_dimensionMode { Resources::ESoundMode::QX_2D },
	_loop {false},
	_playOnAwake {false}
	{}

	SoundEmitter::SoundEmitter(Resources::Sound* sound) noexcept :
	_sound { sound },
	_channel { nullptr },
	_soundMode { QX_SOUNDMODE_DEFAULT },
	_dimensionMode{ Resources::ESoundMode::QX_2D },
	_volume{ 1.f },
	_loop { false },
	_playOnAwake { false }
	{}

	SoundEmitter::SoundEmitter(const SoundEmitter& copy) noexcept :
	_sound { copy._sound },
	_channel { copy._channel },
	_soundMode {copy._soundMode},
	_dimensionMode{ copy._dimensionMode },
	_volume{ copy._volume },
	_loop { copy._loop },
	_playOnAwake { copy._playOnAwake }
	{}

	SoundEmitter::SoundEmitter(SoundEmitter&& copy) noexcept :
	_sound { std::move(copy._sound) },
	_channel { std::move(copy._channel) },
	_soundMode { std::move(copy._soundMode) },
	_dimensionMode{ std::move(copy._dimensionMode) },
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
		_dimensionMode = Resources::ESoundMode::QX_2D;
		_loop = false;
		_playOnAwake = false;
	}

	const QXbool SoundEmitter::PlaySound()
	{
		return _sound->Play(_channel);
	}

	void	SoundEmitter::StopSound()
	{
		FMOD::Channel* channel { _sound->GetChannel() };
		if (channel)
			Core::SoundCore::GetInstance()->Try(channel->stop());
	}

	void SoundEmitter::SetSoundMode(const Resources::ESoundMode& mode)
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

		_dimensionMode = mode;
		_soundMode = soundMode;
		AddSoundMode(_soundMode);
	}

	void SoundEmitter::AddSoundMode(const QXSoundMode& mode)
	{
		_soundMode |= mode;
		Core::SoundCore::GetInstance()->Try(_channel->setMode(_soundMode));
		_sound->ChangeMode(_soundMode);
	}

	void SoundEmitter::DeleteSoundMode(const QXSoundMode& mode)
	{
		_soundMode &= ~mode;
		Core::SoundCore::GetInstance()->Try(_channel->setMode(_soundMode));
		_sound->ChangeMode(_soundMode);
	}

	#pragma endregion
}