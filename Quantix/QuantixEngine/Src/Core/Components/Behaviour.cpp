#include "Core/Components/Behaviour.h"
#include "Core/DataStructure/ResourcesManager.h"
#include "Core/DataStructure/GameObject3D.h"

RTTR_PLUGIN_REGISTRATION
{
	rttr::registration::class_<Quantix::Core::Components::Behaviour>("Behaviour")
	.constructor<>()
	.constructor<const Quantix::Core::Components::Behaviour&>()
	.constructor<Quantix::Core::Components::Behaviour&&>()
	.constructor<Quantix::Core::DataStructure::GameComponent*>();
}

namespace Quantix::Core::Components
{
	Behaviour::Behaviour(Core::DataStructure::GameComponent* object) :
		Component(object)
	{}

	Behaviour* Behaviour::Copy() const
	{
		return new Behaviour(*this);
	}

	void Behaviour::Init(Core::DataStructure::GameComponent* object)
	{
		_object = object;
		_isDestroyed = false;
		_isEnable = true;
		_object->SetToUpdate(true);
		Awake();
	}
}