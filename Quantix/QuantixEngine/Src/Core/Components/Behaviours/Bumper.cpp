#include "Core/Components/Behaviours/Bumper.h"
#include "Core/Components/CharacterController.h"

RTTR_PLUGIN_REGISTRATION
{
	rttr::registration::class_<Quantix::Core::Components::Behaviours::Bumper>("Bumper")
		.constructor<>()
		.constructor<Quantix::Core::DataStructure::GameComponent*>()
		.constructor<const Quantix::Core::Components::Behaviours::Bumper&>()
		.constructor<Quantix::Core::Components::Behaviours::Bumper&&>()
		.property("Force", &Quantix::Core::Components::Behaviours::Bumper::GetForce, &Quantix::Core::Components::Behaviours::Bumper::SetForce);
}

namespace Quantix::Core::Components::Behaviours
{
	Bumper::Bumper(Quantix::Core::DataStructure::GameComponent* par) :
		Component(par),
		Behaviour(par)
	{}

	Bumper* Bumper::Copy() const
	{
		return new Bumper(*this);
	}

	void    Bumper::OnTrigger(Core::DataStructure::GameObject3D* me, Core::DataStructure::GameObject3D* other)
	{
		if (other->GetComponent<Core::Components::Rigidbody>())
			other->GetComponent<Core::Components::Rigidbody>()->AddForce(_force, Physic::ForceMode::IMPULSE);
		else if (other->GetComponent<Core::Components::CharacterController>())
			other->GetComponent<Core::Components::CharacterController>()->_velocity += _force;
	}
}