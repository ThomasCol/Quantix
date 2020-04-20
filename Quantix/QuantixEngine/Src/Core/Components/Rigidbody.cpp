#include "Core/Components/Rigidbody.h"
#include "Core/DataStructure/GameComponent.h"

#include "Physic/PhysicHandler.h"
#include "Physic/PhysicDynamic.h"

#include <iostream>

RTTR_PLUGIN_REGISTRATION
{
	using namespace Quantix::Core::Components;
	rttr::registration::class_<Quantix::Core::Components::Rigidbody>("Rigidbody")
	.property("actorPhysic", &Quantix::Core::Components::Rigidbody::actorPhysic);
}

namespace Quantix::Core::Components
{
	Rigidbody::Rigidbody(DataStructure::GameComponent* par, Physic::PhysicHandler* handler):
		Core::DataStructure::Component(par),
		actorPhysic{ handler->GetObject(par, true) }
	{}

	Rigidbody::Rigidbody(const Rigidbody& src) noexcept :
		Core::DataStructure::Component(src),
		actorPhysic{ src.actorPhysic }
	{}

	Rigidbody::Rigidbody(Rigidbody&& by_ref) noexcept :
		Core::DataStructure::Component(by_ref),
		actorPhysic{ std::move(by_ref.actorPhysic) }
	{}

	void Rigidbody::AddForce(Math::QXvec3 vec) noexcept
	{
		actorPhysic->GetObjectDynamic()->GetRigid()->addForce(physx::PxVec3(vec.x, vec.y, vec.z));
	}

	Rigidbody* Rigidbody::Copy() const
	{
		return new Rigidbody(*this);
	}
}