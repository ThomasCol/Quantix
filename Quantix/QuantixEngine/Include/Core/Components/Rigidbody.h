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
		void SetKinematicTarget(Math::QXvec3 vec) noexcept;

		/**
		 * @brief Get the Mass object
		 * 
		 * @return QXfloat Value of the Mass
		 */
		QXfloat GetMass() noexcept;

		/**
		 * @brief Set the Mass object
		 * 
		 * @param mass new value of Mass
		 */
		void SetMass(QXfloat mass) noexcept;

		/**
		 * @brief Get the Linear Velocity object
		 * 
		 * @return Math::QXvec3 Value of Linear Velocity
		 */
		Math::QXvec3 GetLinearVelocity() noexcept;

		/**
		 * @brief Set the Linear Velocity object
		 * 
		 * @param linVelo New Value of LinearVelocity
		 */
		void SetLinearVelocity(Math::QXvec3 linVelo) noexcept;

		/**
		 * @brief Get the Angular Velocity object
		 * 
		 * @return Math::QXvec3 Value of Angular Velocity
		 */
		Math::QXvec3 GetAngularVelocity() noexcept;

		/**
		 * @brief Set the Angular Velocity object
		 * 
		 * @param angVelo new Value of Angular Velocity
		 */
		void SetAngularVelocity(Math::QXvec3 angVelo) noexcept;

		/**
		 * @brief Get the Transform Position object
		 * 
		 * @return Math::QXvec3 Position value
		 */
		Math::QXvec3 GetTransformPosition() noexcept;

		/**
		 * @brief Set the Transform Position object
		 * 
		 * @param v new Position
		 */
		void SetTransformPosition(Math::QXvec3 v) noexcept;

		/**
		 * @brief Get the Transform Rotation object
		 * 
		 * @return Math::QXquaternion Value of Rotation
		 */
		Math::QXquaternion GetTransformRotation() noexcept;

		/**
		 * @brief Set the Transform Rotation object
		 * 
		 * @param q New Rotation Value
		 */
		void SetTransformRotation(Math::QXquaternion q) noexcept;

		/**
	 	* @brief Get the Rigid Flag Kinematic object
	 	*
	 	* @return Value of the Flag
	 	*/
		bool GetRigidFlagKinematic()				noexcept { return rigidFlag.kinematic; }
		bool GetRigidFlagCCD()						noexcept { return rigidFlag.ccd; }
		bool GetRigidFlagCCDFriction()				noexcept { return rigidFlag.ccdFriction; }
		bool GetRigidFlagSpeculativeCCD()			noexcept { return rigidFlag.speculativeCCD; }
		bool GetRigidFlagRetainAcceleration()		noexcept { return rigidFlag.retainAcceleration; }

		/**
		 * @brief Get the Rigid Flag Kine For Queries object
		 * 
		 * @return true if Kinematic used for queries
		 */
		bool GetRigidFlagKineForQueries()			noexcept { return rigidFlag.useKinematicTargetForQueries; }
		
		bool GetRigidFlagPosePreview()				noexcept { return rigidFlag.poseIntegrationPreview; }
		bool GetRigidFlagCCDMaxContactImpulse()		noexcept { return rigidFlag.ccdMaxContactImpulse; }

		void SetRigidFlagCCD(bool b) noexcept
		{
			rigidFlag.ccd = b;
			actorPhysic->GetRigid()->setRigidBodyFlag(physx::PxRigidBodyFlag::eENABLE_CCD, b);
		}

		void SetRigidFlagCCDFriction(bool b) noexcept
		{
			rigidFlag.ccdFriction = b;
			actorPhysic->GetRigid()->setRigidBodyFlag(physx::PxRigidBodyFlag::eENABLE_CCD_FRICTION, b);
		}

		void SetRigidFlagSpeculativeCCD(bool b) noexcept
		{
			rigidFlag.speculativeCCD = b;
			actorPhysic->GetRigid()->setRigidBodyFlag(physx::PxRigidBodyFlag::eENABLE_SPECULATIVE_CCD, b);
		}

		/**
		 * @brief Set the Rigid Flag Kinematic object
		 *
		 * @param b new Value of the flag
		 */
		void SetRigidFlagKinematic(bool b) noexcept
		{
			rigidFlag.kinematic = b;
			actorPhysic->GetRigid()->setRigidBodyFlag(physx::PxRigidBodyFlag::eKINEMATIC, b);
		}

		void SetRigidFlagRetainAcceleration(bool b) noexcept
		{
			rigidFlag.retainAcceleration = b;
			actorPhysic->GetRigid()->setRigidBodyFlag(physx::PxRigidBodyFlag::eRETAIN_ACCELERATIONS, b);
		}

		/**
		 * @brief Set the Rigid Flag Kine For Queries object
		 * 
		 * @param b 
		 */
		void SetRigidFlagKineForQueries(bool b) noexcept
		{
			rigidFlag.useKinematicTargetForQueries = b;
			actorPhysic->GetRigid()->setRigidBodyFlag(physx::PxRigidBodyFlag::eUSE_KINEMATIC_TARGET_FOR_SCENE_QUERIES, b);
		}

		void SetRigidFlagPosePreview(bool b) noexcept
		{
			rigidFlag.poseIntegrationPreview = b;
			actorPhysic->GetRigid()->setRigidBodyFlag(physx::PxRigidBodyFlag::eENABLE_POSE_INTEGRATION_PREVIEW, b);
		}

		void SetRigidFlagCCDMaxContactImpulse(bool b) noexcept
		{
			rigidFlag.ccdMaxContactImpulse = b;
			actorPhysic->GetRigid()->setRigidBodyFlag(physx::PxRigidBodyFlag::eENABLE_CCD_MAX_CONTACT_IMPULSE, b);
		}

		/**
		 * @brief Set the Actor Flag Disable Gravity object
		 *
		 * @param b new Value of the Flag
		 */
		void SetActorFlagDisableGravity(bool b) noexcept
		{
			actorFlag.disableGravity = b;
			actorPhysic->GetRigid()->setActorFlag(physx::PxActorFlag::eDISABLE_GRAVITY, b);
		}

		/**
		 * @brief Set the Actor Flag Disable Simulation object
		 *
		 * @param b new Value of the Flag
		 */
		void SetActorFlagDisableSimulation(bool b) noexcept
		{
			actorFlag.disableSimulation = b;
			actorPhysic->GetRigid()->setActorFlag(physx::PxActorFlag::eDISABLE_SIMULATION, b);
		}

		void SetActorFlagSendSleepNotifies(bool b) noexcept
		{
			actorFlag.sendSleepNotifies = b;
			actorPhysic->GetRigid()->setActorFlag(physx::PxActorFlag::eSEND_SLEEP_NOTIFIES, b);
		}

		/**
		 * @brief Get the Actor Flag Disable Gravity object
		 *
		 * @return Value of the flag
		 */
		bool GetActorFlagDisableGravity() noexcept { return actorFlag.disableGravity; }


		void SetActorFlagVisualisation(bool b) noexcept
		{
			actorFlag.visualization = b;
			actorPhysic->GetRigid()->setActorFlag(physx::PxActorFlag::eVISUALIZATION, b);
		}

		bool GetActorFlagVisualisation() noexcept { return actorFlag.visualization; }

		/**
		* @brief Get the Actor Flag Disable Simulation object
		*
		* @return Value of the flag
		*/
		bool GetActorFlagDisableSimulation() noexcept { return actorFlag.disableSimulation; }

		bool GetActorFlagSendSleepNotifies() noexcept { return actorFlag.sendSleepNotifies; }

		/**
		 * @brief Get the Rigid Lock Flag Linear X object
		 * 
		 * @return true if LinearX is lock
		 */
		bool GetRigidLockFlagLinearX() noexcept { return rigidLockFlag.lockLinearX; }
	
		/**
		 * @brief Get the Rigid Lock Flag Linear Y object
		 * 
		 * @return true if LinearY is lock
		 */
		bool GetRigidLockFlagLinearY() noexcept { return rigidLockFlag.lockLinearY; }

		/**
		 * @brief Get the Rigid Lock Flag Linear Z object
		 * 
		 * @return true if LinearZ is lock
		 */
		bool GetRigidLockFlagLinearZ() noexcept { return rigidLockFlag.lockLinearZ; }

		/**
		 * @brief Get the Rigid Lock Flag angular X object
		 * 
		 * @return true if angular X is lock
		 */
		bool GetRigidLockFlagAngularX() noexcept { return rigidLockFlag.lockAngularX; }

		/**
		 * @brief Get the Rigid Lock Flag angular Y object
		 * 
		 * @return true if angular Y is lock
		 */
		bool GetRigidLockFlagAngularY() noexcept { return rigidLockFlag.lockAngularY; }

		/**
		 * @brief Get the Rigid Lock Flag angular Z object
		 * 
		 * @return true if angular Z is lock
		 */
		bool GetRigidLockFlagAngularZ() noexcept { return rigidLockFlag.lockAngularZ; }

		/**
		 * @brief Set the Rigid Lock Flag Linear X object
		 * 
		 * @param b 
		 */
		void SetRigidLockFlagLinearX(bool b) noexcept;

		/**
		 * @brief Set the Rigid Lock Flag Linear Y object
		 * 
		 * @param b 
		 */
		void SetRigidLockFlagLinearY(bool b) noexcept;

		/**
		 * @brief Set the Rigid Lock Flag Linear Z object
		 * 
		 * @param b 
		 */
		void SetRigidLockFlagLinearZ(bool b) noexcept;

		/**
		 * @brief Set the Rigid Lock Flag Angular X object
		 * 
		 * @param b 
		 */
		void SetRigidLockFlagAngularX(bool b) noexcept;

		/**
		 * @brief Set the Rigid Lock Flag Angular Y object
		 * 
		 * @param b 
		 */
		void SetRigidLockFlagAngularY(bool b) noexcept;

		/**
		 * @brief Set the Rigid Lock Flag Angular Z object
		 * 
		 * @param b 
		 */
		void SetRigidLockFlagAngularZ(bool b) noexcept;
#pragma endregion 

		CLASS_REGISTRATION(Core::DataStructure::Component);
	};
}

#endif

