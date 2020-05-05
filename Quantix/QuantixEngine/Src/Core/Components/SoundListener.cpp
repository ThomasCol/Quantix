#include "Core\Components\SoundListener.h"

#include <Vec3.h>

#include "Core\SoundCore.h"
#include "Core\DataStructure\GameObject3D.h"

RTTR_PLUGIN_REGISTRATION
{
	rttr::registration::class_<Quantix::Core::Components::SoundListener>("SoundListener")
	.constructor<>()
	.constructor<const Quantix::Core::Components::SoundListener&>()
	.constructor<Quantix::Core::Components::SoundListener&&>()
	.method("AttributesListener", &Quantix::Core::Components::SoundListener::UpdateAttributes);
}

namespace Quantix::Core::Components
{
	#pragma region Constructors & Destructor

	SoundListener::SoundListener() :
	_listenerID{ Quantix::Core::SoundCore::GetInstance()->AddListener() }
	{}

	SoundListener::SoundListener(const SoundListener& copy) noexcept :
	_listenerID {copy._listenerID}
	{}

	SoundListener::SoundListener(SoundListener&& copy) noexcept :
	_listenerID { std::move(copy._listenerID) }
	{}

	SoundListener::~SoundListener()
	{
		Quantix::Core::SoundCore::GetInstance()->SuppListener(_listenerID);
	}

	#pragma endregion

	#pragma region Methods

	SoundListener* SoundListener::Copy() const
	{
		return new SoundListener(*this);
	}

	void SoundListener::Init(Quantix::Core::DataStructure::GameComponent* object)
	{
		_object = object;
		_listenerID = Quantix::Core::SoundCore::GetInstance()->AddListener();
	}

	void SoundListener::UpdateAttributes()
	{
		DataStructure::GameObject3D* go = static_cast<DataStructure::GameObject3D*>(_object);

		//Works if the rotation is a Quaternion
		Math::QXvec3 forw = go->GetTransform()->GetForward();
		Math::QXvec3 upT = go->GetTransform()->GetUp();

		FMOD_VECTOR forward{ forw.x, forw.y , forw.z };
		FMOD_VECTOR pos{ go->GetTransform()->GetPosition().x, go->GetTransform()->GetPosition().y, go->GetTransform()->GetPosition().z };
		FMOD_VECTOR up{ upT.x, upT.y, upT.z };

		Core::SoundCore::GetInstance()->Try(Core::SoundCore::GetInstance()->GetSystem()->set3DListenerAttributes(0, &pos, nullptr, &forward, &up));
	}

	#pragma endregion
}