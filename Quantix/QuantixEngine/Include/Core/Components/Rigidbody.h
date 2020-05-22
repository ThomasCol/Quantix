#ifndef __RIGIDBODY_H__
#define __RIGIDBODY_H__

#include "Core/DLLHeader.h"
#include "Core/DataStructure/Component.h"
#include "rttrEnabled.h"

#include "Physic/IPhysicType.h"
#include "Physic/PhysicHandler.h"
#include "Core/MathHeader.h"
#include "Core/Event/Event.h"
#include "Physic/PhysicSetting.h"

namespace Quantix::Core::DataStructure
{
	class GameComponent;
}

namespace Quantix::Core::Components
{
	struct QUANTIX_API Rigidbody : public virtual Core::DataStructure::Component
	{
#pragma region Attributes
		Physic::PhysicDynamic* actorPhysic{ nullptr };

		Physic::ActorFlag actorFlag;
		Physic::RigidBodyFlag rigidFlag;
		Physic::RigidBodyLockFlag rigidLockFlag;
		QXfloat mass {1.f};

#pragma endregion

#pragma region Constructors

		/**
		 * @brief Construct a new Rigidbody object
		 * 
		 */
		Rigidbody() = default;

		/**
		 * @brief Construct a new Rigidbody object
		 * 
		 * @param par Parent of the Rigidbody
		 */
		Rigidbody(DataStructure::GameComponent* par);

		/**
		 * @brief Construct a new Rigidbody object
		 * 
		 * @param src Rigidbody to copy
		 */
		Rigidbody(const Rigidbody& src) noexcept;

		/**
		 * @brief Construct a new Rigidbody object
		 * 
		 * @param src Rigidbody to move
		 */
		Rigidbody(Rigidbody&& src) noexcept;

		/**
		 * @brief Destroy the Rigidbody object
		 * 
		 */
		~Rigidbody() noexcept = default;

#pragma endregion

#pragma region Functions

		/**
		 * @brief Add Force On The Rigidbody
		 * 
		 * @param vec Force To Add
		 */
		void AddForce(Math::QXvec3 vec, Physic::ForceMode mode = Physic::ForceMode::FORCE) noexcept;

		/**
		 * @brief Add Torque On The Rigidbody
		 *
		 * @param vec Torque To Add
		 */
		void AddTorque(Math::QXvec3 vec) noexcept;

		/**
		 * @brief Copy a Rigidbody
		 * 
		 * @return Rigidbody* new Rigidbody
		 */
		Rigidbody* Copy() const;

		/**
		 * @brief Init a Rigidbody
		 * 
		 * @param par Parent of the Rigidbody
		 */
		void Init(DataStructure::GameComponent* par);

		/**
		 * @brief Destory the RigidBody
		 * 
		 */
		void Destroy() override;

#pragma endregion

#pragma region Accessors 

		/**
		 * @brief Set the Kinematic Target object
		 * 
		 * @param vec 
		 */
		void SetKinematicTarget(Math::QXvec3 vec);

		/**
		 * @brief Get the Mass object
		 * 
		 * @return QXfloat Value of the Mass
		 */
		QXfloat GetMass();

		/**
		 * @brief Set the Mass object
		 * 
		 * @param mass new value of Mass
		 */
		void SetMass(QXfloat mass);

		/**
		 * @brief Get the Linear Velocity object
		 * 
		 * @return Math::QXvec3 Value of Linear Velocity
		 */
		Math::QXvec3 GetLinearVelocity();

		/**
		 * @brief Set the Linear Velocity object
		 * 
		 * @param linVelo New Value of LinearVelocity
		 */
		void SetLinearVelocity(Math::QXvec3 linVelo);

		/**
		 * @brief Get the Angular Velocity object
		 * 
		 * @return Math::QXvec3 Value of Angular Velocity
		 */
		Math::QXvec3 GetAngularVelocity();

		/**
		 * @brief Set the Angular Velocity object
		 * 
		 * @param angVelo new Value of Angular Velocity
		 */
		void SetAngularVelocity(Math::QXvec3 angVelo);

		/**
		 * @brief Get the Transform Position object
		 * 
		 * @return Math::QXvec3 Position value
		 */
		Math::QXvec3 GetTransformPosition();

		/**
		 * @brief Set the Transform Position object
		 * 
		 * @param v new Position
		 */
		void SetTransformPosition(Math::QXvec3 v);

		/**
		 * @brief Get the Transform Rotation object
		 * 
		 * @return Math::QXquaternion Value of Rotation
		 */
		Math::QXquaternion GetTransformRotation();

		/**
		 * @brief Set the Transform Rotation object
		 * 
		 * @param q New Rotation Value
		 */
		void SetTransformRotation(Math::QXquaternion q);

		/**
	 	* @brief Get the Rigid Flag Kinematic object
	 	*
	 	* @return Value of the Flag
	 	*/
		bool GetRigidFlagKinematic() { return rigidFlag.kinematic; }
		bool GetRigidFlagCCD() { return rigidFlag.ccd; }
		bool GetRigidFlagCCDFriction() { return rigidFlag.ccdFriction; }
		bool GetRigidFlagSpeculativeCCD() { return rigidFlag.speculativeCCD; }
		bool GetRigidFlagRetainAcceleration() { return rigidFlag.retainAcceleration; }

		/**
		 * @brief Get the Rigid Flag Kine For Queries object
		 * 
		 * @return true if Kinematic used for queries
		 */
		bool GetRigidFlagKineForQueries() { return rigidFlag.useKinematicTargetForQueries; }
		
		bool GetRigidFlagPosePreview() { return rigidFlag.poseIntegrationPreview; }
		bool GetRigidFlagCCDMaxContactImpulse() { return rigidFlag.ccdMaxContactImpulse; }

		void SetRigidFlagCCD(bool b)
		{
			rigidFlag.ccd = b;
			actorPhysic->GetRigid()->setRigidBodyFlag(physx::PxRigidBodyFlag::eENABLE_CCD, b);
		}

		void SetRigidFlagCCDFriction(bool b)
		{
			rigidFlag.ccdFriction = b;
			actorPhysic->GetRigid()->setRigidBodyFlag(physx::PxRigidBodyFlag::eENABLE_CCD_FRICTION, b);
		}

		void SetRigidFlagSpeculativeCCD(bool b)
		{
			rigidFlag.speculativeCCD = b;
			actorPhysic->GetRigid()->setRigidBodyFlag(physx::PxRigidBodyFlag::eENABLE_SPECULATIVE_CCD, b);
		}

		/**
		 * @brief Set the Rigid Flag Kinematic object
		 *
		 * @param b new Value of the flag
		 */
		void SetRigidFlagKinematic(bool b)
		{
			rigidFlag.kinematic = b;
			actorPhysic->GetRigid()->setRigidBodyFlag(physx::PxRigidBodyFlag::eKINEMATIC, b);
		}

		void SetRigidFlagRetainAcceleration(bool b)
		{
			rigidFlag.retainAcceleration = b;
			actorPhysic->GetRigid()->setRigidBodyFlag(physx::PxRigidBodyFlag::eRETAIN_ACCELERATIONS, b);
		}

		/**
		 * @brief Set the Rigid Flag Kine For Queries object
		 * 
		 * @param b 
		 */
		void SetRigidFlagKineForQueries(bool b)
		{
			rigidFlag.useKinematicTargetForQueries = b;
			actorPhysic->GetRigid()->setRigidBodyFlag(physx::PxRigidBodyFlag::eUSE_KINEMATIC_TARGET_FOR_SCENE_QUERIES, b);
		}

		void SetRigidFlagPosePreview(bool b)
		{
			rigidFlag.poseIntegrationPreview = b;
			actorPhysic->GetRigid()->setRigidBodyFlag(physx::PxRigidBodyFlag::eENABLE_POSE_INTEGRATION_PREVIEW, b);
		}

		void SetRigidFlagCCDMaxContactImpulse(bool b)
		{
			rigidFlag.ccdMaxContactImpulse = b;
			actorPhysic->GetRigid()->setRigidBodyFlag(physx::PxRigidBodyFlag::eENABLE_CCD_MAX_CONTACT_IMPULSE, b);
		}


		/**
		 * @brief Set the Actor Flag Disable Gravity object
		 *
		 * @param b new Value of the Flag
		 */
		void SetActorFlagDisableGravity(bool b)
		{
			actorFlag.disableGravity = b;
			actorPhysic->GetRigid()->setActorFlag(physx::PxActorFlag::eDISABLE_GRAVITY, b);
		}

		/**
		 * @brief Set the Actor Flag Disable Simulation object
		 *
		 * @param b new Value of the Flag
		 */
		void SetActorFlagDisableSimulation(bool b)
		{
			actorFlag.disableSimulation = b;
			actorPhysic->GetRigid()->setActorFlag(physx::PxActorFlag::eDISABLE_SIMULATION, b);
		}

		void SetActorFlagSendSleepNotifies(bool b)
		{
			actorFlag.sendSleepNotifies = b;
			actorPhysic->GetRigid()->setActorFlag(physx::PxActorFlag::eSEND_SLEEP_NOTIFIES, b);
		}

		/**
		 * @brief Get the Actor Flag Disable Gravity object
		 *
		 * @return Value of the flag
		 */
		bool GetActorFlagDisableGravity() { return actorFlag.disableGravity; }

		/**
		* @brief Get the Actor Flag Disable Simulation object
		*
		* @return Value of the flag
		*/
		bool GetActorFlagDisableSimulation() { return actorFlag.disableSimulation; }

		bool GetActorFlagSendSleepNotifies() { return actorFlag.sendSleepNotifies; }

		/**
		 * @brief Get the Rigid Lock Flag Linear X object
		 * 
		 * @return true if LinearX is lock
		 */
		bool GetRigidLockFlagLinearX() { return rigidLockFlag.lockLinearX; }
	
		/**
		 * @brief Get the Rigid Lock Flag Linear Y object
		 * 
		 * @return true if LinearY is lock
		 */
		bool GetRigidLockFlagLinearY() { return rigidLockFlag.lockLinearY; }

		/**
		 * @brief Get the Rigid Lock Flag Linear Z object
		 * 
		 * @return true if LinearZ is lock
		 */
		bool GetRigidLockFlagLinearZ() { return rigidLockFlag.lockLinearZ; }

		/**
		 * @brief Get the Rigid Lock Flag angular X object
		 * 
		 * @return true if angular X is lock
		 */
		bool GetRigidLockFlagAngularX() { return rigidLockFlag.lockAngularX; }

		/**
		 * @brief Get the Rigid Lock Flag angular Y object
		 * 
		 * @return true if angular Y is lock
		 */
		bool GetRigidLockFlagAngularY() { return rigidLockFlag.lockAngularY; }

		/**
		 * @brief Get the Rigid Lock Flag angular Z object
		 * 
		 * @return true if angular Z is lock
		 */
		bool GetRigidLockFlagAngularZ() { return rigidLockFlag.lockAngularZ; }

		/**
		 * @brief Set the Rigid Lock Flag Linear X object
		 * 
		 * @param b 
		 */
		void SetRigidLockFlagLinearX(bool b);

		/**
		 * @brief Set the Rigid Lock Flag Linear Y object
		 * 
		 * @param b 
		 */
		void SetRigidLockFlagLinearY(bool b);

		/**
		 * @brief Set the Rigid Lock Flag Linear Z object
		 * 
		 * @param b 
		 */
		void SetRigidLockFlagLinearZ(bool b);

		/**
		 * @brief Set the Rigid Lock Flag Angular X object
		 * 
		 * @param b 
		 */
		void SetRigidLockFlagAngularX(bool b);

		/**
		 * @brief Set the Rigid Lock Flag Angular Y object
		 * 
		 * @param b 
		 */
		void SetRigidLockFlagAngularY(bool b);

		/**
		 * @brief Set the Rigid Lock Flag Angular Z object
		 * 
		 * @param b 
		 */
		void SetRigidLockFlagAngularZ(bool b);
#pragma endregion 

		CLASS_REGISTRATION(Core::DataStructure::Component);
	};
}

#endif

