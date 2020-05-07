#ifndef __PHYSICSETTING_H__
#define __PHYSICSETTING_H__

#include "Core/DLLHeader.h"
#include "rttrEnabled.h"
#include "Physic/PhysicDynamic.h"

namespace Quantix::Physic
{
	// Filter Collision Group 
	struct QUANTIX_API FilterGroup
	{
		enum Enum
		{
			PAWN = (1 << 0),
			eMINE_HEAD = (1 << 1),
			eCRAB = (1 << 2),
		};
	};

	struct QUANTIX_API CollideGroup
	{
		bool pawn = false;
		bool mine = false;
		bool crab = false;
	};

	// Wrapper PxRigidFlag
	struct QUANTIX_API RigidBodyFlag
	{
		Physic::PhysicDynamic*	actorPhysic{ nullptr };
		bool					ccd = false;
		bool					ccdFriction = false;
		bool					speculativeCCD = false;
		bool					kinematic = false;
		bool					retainAcceleration = false;
		bool					useKinematicTargetForQueries = false;
		bool					poseIntegrationPreview = false;
		bool					ccdMaxContactImpulse = false;

		/**
		 * @brief Get the Rigid Flag Kinematic object
		 *
		 * @return Value of the Flag
		 */
		bool GetRigidFlagKinematic() { return kinematic; }
		bool GetRigidFlagCCD() { return ccd; }
		bool GetRigidFlagCCDFriction() { return ccdFriction; }
		bool GetRigidFlagSpeculativeCCD() { return speculativeCCD; }
		bool GetRigidFlagRetainAcceleration() { return retainAcceleration; }
		bool GetRigidFlagKineForQueries() { return useKinematicTargetForQueries; }
		bool GetRigidFlagPosePreview() { return poseIntegrationPreview; }
		bool GetRigidFlagCCDMaxContactImpulse() { return ccdMaxContactImpulse; }


		void SetRigidFlagCCD(bool b)
		{
			ccd = b;
			actorPhysic->GetRigid()->setRigidBodyFlag(physx::PxRigidBodyFlag::eENABLE_CCD, b);
		}

		void SetRigidFlagCCDFriction(bool b)
		{
			ccdFriction = b;
			actorPhysic->GetRigid()->setRigidBodyFlag(physx::PxRigidBodyFlag::eENABLE_CCD_FRICTION, b);
		}

		void SetRigidFlagSpeculativeCCD(bool b)
		{
			speculativeCCD = b;
			actorPhysic->GetRigid()->setRigidBodyFlag(physx::PxRigidBodyFlag::eENABLE_SPECULATIVE_CCD, b);
		}

		/**
		 * @brief Set the Rigid Flag Kinematic object
		 *
		 * @param b new Value of the flag
		 */
		void SetRigidFlagKinematic(bool b)
		{
			kinematic = b;
			actorPhysic->GetRigid()->setRigidBodyFlag(physx::PxRigidBodyFlag::eKINEMATIC, b);
		}

		void SetRigidFlagRetainAcceleration(bool b)
		{
			retainAcceleration = b;
			actorPhysic->GetRigid()->setRigidBodyFlag(physx::PxRigidBodyFlag::eRETAIN_ACCELERATIONS, b);
		}

		void SetRigidFlagKineForQueries(bool b)
		{
			useKinematicTargetForQueries = b;
			actorPhysic->GetRigid()->setRigidBodyFlag(physx::PxRigidBodyFlag::eUSE_KINEMATIC_TARGET_FOR_SCENE_QUERIES, b);
		}

		void SetRigidFlagPosePreview(bool b)
		{
			poseIntegrationPreview = b;
			actorPhysic->GetRigid()->setRigidBodyFlag(physx::PxRigidBodyFlag::eENABLE_POSE_INTEGRATION_PREVIEW, b);
		}

		void SetRigidFlagCCDMaxContactImpulse(bool b)
		{
			ccdMaxContactImpulse = b;
			actorPhysic->GetRigid()->setRigidBodyFlag(physx::PxRigidBodyFlag::eENABLE_CCD_MAX_CONTACT_IMPULSE, b);
		}

		CLASS_REGISTRATION()
	};

	// Wrapper PxBaseFlag
	struct QUANTIX_API BaseFlag
	{

	};

	// Wrapper PxActorFlag
	struct QUANTIX_API ActorFlag
	{
		Physic::PhysicDynamic*	actorPhysic{ nullptr };
		bool					disableGravity = false;
		bool					disableSimulation = false;
		bool					sendSleepNotifies = false;
		bool					visualization = false;

		/**
		 * @brief Set the Actor Flag Disable Gravity object
		 *
		 * @param b new Value of the Flag
		 */
		void SetActorFlagDisableGravity(bool b)
		{
			disableGravity = b;
			actorPhysic->GetRigid()->setActorFlag(physx::PxActorFlag::eDISABLE_GRAVITY, b);
		}

		/**
		 * @brief Set the Actor Flag Disable Simulation object
		 *
		 * @param b new Value of the Flag
		 */
		void SetActorFlagDisableSimulation(bool b)
		{
			disableSimulation = b;
			actorPhysic->GetRigid()->setActorFlag(physx::PxActorFlag::eDISABLE_SIMULATION, b);
		}

		void SetActorFlagSendSleepNotifies(bool b)
		{
			sendSleepNotifies = b;
			actorPhysic->GetRigid()->setActorFlag(physx::PxActorFlag::eSEND_SLEEP_NOTIFIES, b);
		}

		/**
		 * @brief Get the Actor Flag Disable Gravity object
		 *
		 * @return Value of the flag
		 */
		bool GetActorFlagDisableGravity() { return disableGravity; }

		/**
		* @brief Get the Actor Flag Disable Simulation object
		*
		* @return Value of the flag
		*/
		bool GetActorFlagDisableSimulation() { return disableSimulation; }

		bool GetActorFlagSendSleepNotifies() { return sendSleepNotifies; }


		CLASS_REGISTRATION()
	};

	// Wrapper PxShapeFlag
	struct QUANTIX_API ShapeFlag
	{
		bool sceneQuery = true;
		bool simulation = true;
		bool trigger = false;
		bool visualization = false;
	};

	// Wrapper PxSceneFlag
	struct QUANTIX_API SceneFlag
	{
		bool adaptiveForce = false;
		bool disableCCDResweep = false;
		bool disableContactCache = false;
		bool disableContactReportResize = false;
		bool activeActors = true;
		bool averagePoint = false;
		bool ccd = false;
		bool enhancedDeterminism = false;
		bool frictionEveryIteration = false;
		bool gpuDynamics = false;
		bool pcm = false;
		bool stabilization = false;
		bool excludeKineActiveActors = false;
		bool mutableFlags = false;
		bool requireRWLock = false;
	};
}

#endif // !__PHYSICSETTING_H__
