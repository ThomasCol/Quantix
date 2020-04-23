#include "Core/Components/Rigidbody.h"
#include "Core/DataStructure/GameComponent.h"

#include "Physic/PhysicHandler.h"
#include "Physic/PhysicDynamic.h"

#include "Physic/PhysicHandler.h"

#include "Core/MathHeader.h"

#include <iostream>

RTTR_PLUGIN_REGISTRATION
{
	using namespace Quantix::Core::Components;
	rttr::registration::class_<Quantix::Core::Components::Rigidbody>("Rigidbody")
	.constructor<>()
	.constructor<Quantix::Core::DataStructure::GameComponent*>()
	.constructor<const Quantix::Core::Components::Rigidbody&>()
	.constructor<Quantix::Core::Components::Rigidbody&&>()
	.property("Mass", &Quantix::Core::Components::Rigidbody::GetMass, &Quantix::Core::Components::Rigidbody::SetMass)
	.property("LinearVelocity", &Quantix::Core::Components::Rigidbody::GetLinearVelocity, &Quantix::Core::Components::Rigidbody::SetLinearVelocity)
	.property("AngularVelocity", &Quantix::Core::Components::Rigidbody::GetAngularVelocity, &Quantix::Core::Components::Rigidbody::SetAngularVelocity);
}

namespace Quantix::Core::Components
{
	Rigidbody::Rigidbody(DataStructure::GameComponent* par):
		Core::DataStructure::Component(par),
		actorPhysic{ (Physic::PhysicDynamic*)Physic::PhysicHandler::GetInstance()->GetObject(par, true) }
	{

	}

	Rigidbody::Rigidbody(const Rigidbody& src) noexcept :
		Core::DataStructure::Component(src),
		actorPhysic{ src.actorPhysic }
	{
		if (!actorPhysic)
			actorPhysic = (Physic::PhysicDynamic*)Physic::PhysicHandler::GetInstance()->GetObject(src._object, true);
	}

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

	QXfloat Rigidbody::GetMass()
	{
		return (QXfloat)actorPhysic->GetRigid()->getMass();
	}

	void Rigidbody::SetMass(QXfloat m)
	{
		actorPhysic->GetRigid()->setMass(m);
	}

	Math::QXvec3 Rigidbody::GetLinearVelocity()
	{
		physx::PxVec3 v = actorPhysic->GetRigid()->getAngularVelocity();
		return 	Math::QXvec3(v.x, v.y, v.z);
	}

	void Rigidbody::SetLinearVelocity(Math::QXvec3 v)
	{
		actorPhysic->GetRigid()->setLinearVelocity(physx::PxVec3(v.x, v.y, v.z));
	}

	Math::QXvec3 Rigidbody::GetAngularVelocity()
	{
		physx::PxVec3 v = actorPhysic->GetRigid()->getAngularVelocity();
		return 	Math::QXvec3(v.x, v.y, v.z);
	}

	void Rigidbody::SetAngularVelocity(Math::QXvec3 v)
	{
		actorPhysic->GetRigid()->setAngularVelocity(physx::PxVec3(v.x, v.y, v.z));
	}
}