#include "Core/Components/Rigidbody.h"
#include "Core/DataStructure/GameComponent.h"

#include "Physic/PhysicHandler.h"
#include "Physic/PhysicDynamic.h"
#include <functional>

#include "Core/MathHeader.h"

#include <iostream>

RTTR_PLUGIN_REGISTRATION
{
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
			(rttr::metadata("Description", "Actor Flags"))
	.property("DisableSimulation", &Quantix::Core::Components::Rigidbody::GetActorFlagDisableSimulation, &Quantix::Core::Components::Rigidbody::SetActorFlagDisableSimulation)
			(rttr::metadata("Description", "End"))
	.property("Kinematic", &Quantix::Core::Components::Rigidbody::GetRigidFlagKinematic, &Quantix::Core::Components::Rigidbody::SetRigidFlagKinematic)
			(rttr::metadata("Description", "Rigid Flags"))
	.property("CCD", &Quantix::Core::Components::Rigidbody::GetRigidFlagCCD, &Quantix::Core::Components::Rigidbody::SetRigidFlagCCD)
	.property("CCDFriction", &Quantix::Core::Components::Rigidbody::GetRigidFlagCCDFriction, &Quantix::Core::Components::Rigidbody::SetRigidFlagCCDFriction)
	.property("SpeculativeCCD", &Quantix::Core::Components::Rigidbody::GetRigidFlagSpeculativeCCD, &Quantix::Core::Components::Rigidbody::SetRigidFlagSpeculativeCCD)
	.property("RetainAcceleration", &Quantix::Core::Components::Rigidbody::GetRigidFlagRetainAcceleration, &Quantix::Core::Components::Rigidbody::SetRigidFlagRetainAcceleration)
	.property("KinematicQueries", &Quantix::Core::Components::Rigidbody::GetRigidFlagKineForQueries, &Quantix::Core::Components::Rigidbody::SetRigidFlagKineForQueries)
	.property("PoseIntPreview", &Quantix::Core::Components::Rigidbody::GetRigidFlagPosePreview, &Quantix::Core::Components::Rigidbody::SetRigidFlagPosePreview)
	.property("CCDMaxImpulse", &Quantix::Core::Components::Rigidbody::GetRigidFlagCCDMaxContactImpulse, &Quantix::Core::Components::Rigidbody::SetRigidFlagCCDMaxContactImpulse)
			(rttr::metadata("Description", "End"))
	.property("LockLinearX", &Quantix::Core::Components::Rigidbody::GetRigidLockFlagLinearX, &Quantix::Core::Components::Rigidbody::SetRigidLockFlagLinearX)
		(rttr::metadata("Description", "RigidLock Flags"))
	.property("LockLinearY", &Quantix::Core::Components::Rigidbody::GetRigidLockFlagLinearY, &Quantix::Core::Components::Rigidbody::SetRigidLockFlagLinearY)
	.property("LockLinearZ", &Quantix::Core::Components::Rigidbody::GetRigidLockFlagLinearZ, &Quantix::Core::Components::Rigidbody::SetRigidLockFlagLinearZ)
	.property("LockAngularX", &Quantix::Core::Components::Rigidbody::GetRigidLockFlagAngularX, &Quantix::Core::Components::Rigidbody::SetRigidLockFlagAngularX)
	.property("LockAngularY", &Quantix::Core::Components::Rigidbody::GetRigidLockFlagAngularY, &Quantix::Core::Components::Rigidbody::SetRigidLockFlagAngularY)
	.property("LockAngularZ", &Quantix::Core::Components::Rigidbody::GetRigidLockFlagAngularZ, &Quantix::Core::Components::Rigidbody::SetRigidLockFlagAngularZ)
		(rttr::metadata("Description", "End"));

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
	}

	Rigidbody::Rigidbody(Rigidbody&& by_ref) noexcept :
		Core::DataStructure::Component(by_ref),
		actorPhysic{ std::move(by_ref.actorPhysic) }
	{}

	void Rigidbody::AddForce(Math::QXvec3 vec, Physic::ForceMode mode) noexcept
	{
		if (mode == Physic::ForceMode::ACCELERATION)
			actorPhysic->GetObjectDynamic()->GetRigid()->addForce(physx::PxVec3(vec.x, vec.y, vec.z), physx::PxForceMode::eACCELERATION);
		else if (mode == Physic::ForceMode::IMPULSE)
			actorPhysic->GetObjectDynamic()->GetRigid()->addForce(physx::PxVec3(vec.x, vec.y, vec.z), physx::PxForceMode::eIMPULSE);
		else if (mode == Physic::ForceMode::VELOCITYCHANGE)
			actorPhysic->GetObjectDynamic()->GetRigid()->addForce(physx::PxVec3(vec.x, vec.y, vec.z), physx::PxForceMode::eVELOCITY_CHANGE);
		else
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

		Camera* cam = _object->GetComponent<Camera>();
		/*if (cam)
			cam->ActualizeRigid(this);*/

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

	void Rigidbody::SetRigidLockFlagLinearX(bool b)
	{
		rigidLockFlag.lockLinearX = b;

		actorPhysic->GetRigid()->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_LINEAR_X, b);
	}

	void Rigidbody::SetRigidLockFlagLinearY(bool b)
	{
		rigidLockFlag.lockLinearY = b;

		actorPhysic->GetRigid()->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_LINEAR_Y, b);
	}

	void Rigidbody::SetRigidLockFlagLinearZ(bool b)
	{
		rigidLockFlag.lockLinearZ = b;

		actorPhysic->GetRigid()->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_LINEAR_Z, b);
	}

	void Rigidbody::SetRigidLockFlagAngularX(bool b)
	{
		rigidLockFlag.lockAngularX = b;

		actorPhysic->GetRigid()->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_X, b);
	}

	void Rigidbody::SetRigidLockFlagAngularY(bool b)
	{
		rigidLockFlag.lockAngularY = b;

		actorPhysic->GetRigid()->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y, b);
	}

	void Rigidbody::SetRigidLockFlagAngularZ(bool b)
	{
		rigidLockFlag.lockAngularZ = b;

		actorPhysic->GetRigid()->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z, b);
	}
}
