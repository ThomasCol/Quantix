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
	.property("Linear Velocity", &Quantix::Core::Components::Rigidbody::GetLinearVelocity, &Quantix::Core::Components::Rigidbody::SetLinearVelocity)
	.property("Angular Velocity", &Quantix::Core::Components::Rigidbody::GetAngularVelocity, &Quantix::Core::Components::Rigidbody::SetAngularVelocity)
	.property("Position", &Quantix::Core::Components::Rigidbody::GetTransformPosition, &Quantix::Core::Components::Rigidbody::SetTransformPosition)
	.property("Rotation", &Quantix::Core::Components::Rigidbody::GetTransformRotation, &Quantix::Core::Components::Rigidbody::SetTransformRotation);

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

	Math::QXvec3 Rigidbody::GetTransformPosition()
	{
		physx::PxVec3 v = actorPhysic->GetRigid()->getGlobalPose().p;
		return 	Math::QXvec3(v.x, v.y, v.z);
	}

	void Rigidbody::SetTransformPosition(Math::QXvec3 v)
	{
		actorPhysic->GetRigid()->setGlobalPose(physx::PxTransform(
												physx::PxVec3(v.x, v.y, v.z),
												actorPhysic->GetRigid()->getGlobalPose().q));
	}

	Math::QXquaternion Rigidbody::GetTransformRotation()
	{
		physx::PxQuat q = actorPhysic->GetRigid()->getGlobalPose().q;
		return 	Math::QXquaternion(q.w, q.x, q.y, q.z);
	}

	void Rigidbody::SetTransformRotation(Math::QXquaternion q)
	{
		actorPhysic->GetRigid()->setGlobalPose(physx::PxTransform(
												actorPhysic->GetRigid()->getGlobalPose().p, 
												physx::PxQuat(q.v.x, q.v.y, q.v.z, q.w)
												));

		//actorPhysic->GetRigid()->fla
		//physx::PxBaseFlag::
		//physx::PxRigidBodyFlag::
	}

	void Rigidbody::SetActorFlagDisableGravity(bool b)
	{
		actorFlag.disableGravity = b;
		actorPhysic->GetRigid()->setActorFlag(physx::PxActorFlag::eDISABLE_GRAVITY, b);
	}

	bool Rigidbody::GetActorFlagDisableGravity()
	{
		return actorFlag.disableGravity;
	}

	void Rigidbody::SetActorFlagDisableSimulation(bool b)
	{
		actorFlag.disableSimulation = b;
		actorPhysic->GetRigid()->setActorFlag(physx::PxActorFlag::eDISABLE_SIMULATION, b);
	}

	bool Rigidbody::GetActorFlagDisableSimulation()
	{
		return actorFlag.disableSimulation;
	}

	void Rigidbody::SetActorFlagSendSleepNotifies(bool b)
	{
		actorFlag.sendSleepNotifies = b;
		actorPhysic->GetRigid()->setActorFlag(physx::PxActorFlag::eSEND_SLEEP_NOTIFIES, b);
	}

	bool Rigidbody::GetActorFlagSendSleepNotifies()
	{
		return actorFlag.sendSleepNotifies;
	}

	void Rigidbody::SetActorFlagVisualization(bool b)
	{
		actorFlag.visualization = b;
		actorPhysic->GetRigid()->setActorFlag(physx::PxActorFlag::eVISUALIZATION, b);
	}

	bool Rigidbody::GetActorFlagVisualization()
	{
		return actorFlag.visualization;
	}
}