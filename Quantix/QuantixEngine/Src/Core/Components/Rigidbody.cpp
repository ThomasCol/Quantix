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
	.property("AngularVelocity", &Quantix::Core::Components::Rigidbody::GetAngularVelocity, &Quantix::Core::Components::Rigidbody::SetAngularVelocity)
	.property("Position", &Quantix::Core::Components::Rigidbody::GetTransformPosition, &Quantix::Core::Components::Rigidbody::SetTransformPosition)
	.property("Rotation", &Quantix::Core::Components::Rigidbody::GetTransformRotation, &Quantix::Core::Components::Rigidbody::SetTransformRotation)
	.property("DisableGravity", &Quantix::Core::Components::Rigidbody::GetActorFlagDisableGravity, &Quantix::Core::Components::Rigidbody::SetActorFlagDisableGravity)
	.property("DisableSimulation", &Quantix::Core::Components::Rigidbody::GetActorFlagDisableSimulation, &Quantix::Core::Components::Rigidbody::SetActorFlagDisableSimulation)
	.property("CCD", &Quantix::Core::Components::Rigidbody::GetRigidFlagCCD, &Quantix::Core::Components::Rigidbody::SetRigidFlagCCD)
	.property("CCDFriction", &Quantix::Core::Components::Rigidbody::GetRigidFlagCCDFriction, &Quantix::Core::Components::Rigidbody::SetRigidFlagCCDFriction)
	.property("SpeculativeCCD", &Quantix::Core::Components::Rigidbody::GetRigidFlagSpeculativeCCD, &Quantix::Core::Components::Rigidbody::SetRigidFlagSpeculativeCCD)
	.property("Kinematic", &Quantix::Core::Components::Rigidbody::GetRigidFlagKinematic, &Quantix::Core::Components::Rigidbody::SetRigidFlagKinematic)
	.property("RetainAcceleration", &Quantix::Core::Components::Rigidbody::GetRigidFlagRetainAcceleration, &Quantix::Core::Components::Rigidbody::SetRigidFlagRetainAcceleration)
	.property("KinematicQueries", &Quantix::Core::Components::Rigidbody::GetRigidFlagKineForQueries, &Quantix::Core::Components::Rigidbody::SetRigidFlagKineForQueries)
	.property("PoseIntPreview", &Quantix::Core::Components::Rigidbody::GetActorFlagPosePreview, &Quantix::Core::Components::Rigidbody::SetRigidFlagPosePreview)
	.property("CCDMaxImpulse", &Quantix::Core::Components::Rigidbody::GetActorFlagCCDMaxContactImpulse, &Quantix::Core::Components::Rigidbody::SetActorFlagCCDMaxContactImpulse);
}

namespace Quantix::Core::Components
{
	Rigidbody::Rigidbody(DataStructure::GameComponent* par):
		Core::DataStructure::Component(par),
		actorPhysic{ (Physic::PhysicDynamic*)Physic::PhysicHandler::GetInstance()->GetObject(par, true) }
	{}

	Rigidbody::Rigidbody(const Rigidbody& src) noexcept :
		Core::DataStructure::Component(src),
		actorPhysic{ src.actorPhysic }
	{
	}

	Rigidbody::Rigidbody(Rigidbody&& by_ref) noexcept :
		Core::DataStructure::Component(by_ref),
		actorPhysic{ std::move(by_ref.actorPhysic) }
	{}

	void Rigidbody::AddForce(Math::QXvec3 vec) noexcept
	{
		actorPhysic->GetObjectDynamic()->GetRigid()->addForce(physx::PxVec3(vec.x, vec.y, vec.z));
	}

	void Rigidbody::AddTorque(Math::QXvec3 vec) noexcept
	{
		actorPhysic->GetObjectDynamic()->GetRigid()->addTorque(physx::PxVec3(vec.x, vec.y, vec.z));
	}

	Rigidbody* Rigidbody::Copy() const
	{
		return new Rigidbody(*this);
	}

	void Rigidbody::Init(DataStructure::GameComponent* par)
	{
		_object = par;
		_isDestroyed = false;
		_isEnable = true;

		actorPhysic = (Physic::PhysicDynamic*)Physic::PhysicHandler::GetInstance()->GetObject(par, true);

		// Actualize the pointer in colliders
		std::vector<ICollider*> vector{ _object->GetComponents<ICollider>() };
		for (QXuint i = 0; i < vector.size(); i++)
			vector[i]->UpdateActorPhysic();
	}

	void Rigidbody::Destroy()
	{
		// Actualize the physic actor
		Physic::PhysicHandler::GetInstance()->GetObject(_object, false);
		
		// Actualize the pointer in colliders
		std::vector<ICollider*> vector{ _object->GetComponents<ICollider>() };
		for (QXuint i = 0; i < vector.size(); i++)
			vector[i]->UpdateActorPhysic();
	}

	QXfloat Rigidbody::GetMass()
	{
		return mass;
	}

	void Rigidbody::SetMass(QXfloat m)
	{
		if (m < 0.f)
			m = 0.00001f;
		mass = m;
		physx::PxRigidBodyExt::updateMassAndInertia(*actorPhysic->GetRigid(), m);
	}

	Math::QXvec3 Rigidbody::GetLinearVelocity()
	{
		physx::PxVec3 v = actorPhysic->GetRigid()->getLinearVelocity();
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
	}

	void Rigidbody::SetActorFlagDisableGravity(bool b)
	{
		actorFlag.disableGravity = b;
		actorPhysic->GetRigid()->setActorFlag(physx::PxActorFlag::eDISABLE_GRAVITY, b);
	}

	void Rigidbody::SetActorFlagDisableSimulation(bool b)
	{
		actorFlag.disableSimulation = b;
		actorPhysic->GetRigid()->setActorFlag(physx::PxActorFlag::eDISABLE_SIMULATION, b);
	}

	void Rigidbody::SetActorFlagSendSleepNotifies(bool b)
	{
		actorFlag.sendSleepNotifies = b;
		actorPhysic->GetRigid()->setActorFlag(physx::PxActorFlag::eSEND_SLEEP_NOTIFIES, b);
	}

	void Rigidbody::SetRigidFlagCCD(bool b)
	{
		rigidFlag.ccd = b;
		actorPhysic->GetRigid()->setRigidBodyFlag(physx::PxRigidBodyFlag::eENABLE_CCD, b);
	} 

	void Rigidbody::SetRigidFlagCCDFriction(bool b)
	{
		rigidFlag.ccdFriction = b;
		actorPhysic->GetRigid()->setRigidBodyFlag(physx::PxRigidBodyFlag::eENABLE_CCD_FRICTION, b);
	}

	void Rigidbody::SetRigidFlagSpeculativeCCD(bool b)
	{
		rigidFlag.speculativeCCD = b;
		actorPhysic->GetRigid()->setRigidBodyFlag(physx::PxRigidBodyFlag::eENABLE_SPECULATIVE_CCD, b);
	}

	void Rigidbody::SetRigidFlagKinematic(bool b)
	{
		rigidFlag.kinematic = b;
		actorPhysic->GetRigid()->setRigidBodyFlag(physx::PxRigidBodyFlag::eKINEMATIC, b);
	}

	void Rigidbody::SetRigidFlagRetainAcceleration(bool b)
	{
		rigidFlag.retainAcceleration = b;
		actorPhysic->GetRigid()->setRigidBodyFlag(physx::PxRigidBodyFlag::eRETAIN_ACCELERATIONS, b);
	}

	void Rigidbody::SetRigidFlagKineForQueries(bool b)
	{
		rigidFlag.useKinematicTargetForQueries = b;
		actorPhysic->GetRigid()->setRigidBodyFlag(physx::PxRigidBodyFlag::eUSE_KINEMATIC_TARGET_FOR_SCENE_QUERIES, b);
	}

	void Rigidbody::SetRigidFlagPosePreview(bool b)
	{
		rigidFlag.poseIntegrationPreview = b;
		actorPhysic->GetRigid()->setRigidBodyFlag(physx::PxRigidBodyFlag::eENABLE_POSE_INTEGRATION_PREVIEW, b);
	}

	void Rigidbody::SetActorFlagCCDMaxContactImpulse(bool b)
	{
		rigidFlag.ccdMaxContactImpulse = b;
		actorPhysic->GetRigid()->setRigidBodyFlag(physx::PxRigidBodyFlag::eENABLE_CCD_MAX_CONTACT_IMPULSE, b);
	}
}
