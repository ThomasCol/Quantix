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
	{
		object->AddBehaviour(this);
	}

	/*void	Behaviour::Destroy()
	{
		//m_object->RemoveBehaviour(this);
	}*/

	Behaviour* Behaviour::Copy() const
	{
		return new Behaviour(*this);
	}
}