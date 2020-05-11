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
		physx::PxShape* shape{ nullptr };
		
		bool pawn = false;
		bool mine = false;
		bool crab = false;

		bool GetCollideFilterPawn() { return pawn; };
		bool GetCollideFilterMine() { return mine; };
		bool GetCollideFilterCrab() { return crab; };
		void SetCollideFilterPawn(bool b)
		{
			pawn = b;
			std::cout << "pawn : " << pawn << std::endl;

			physx::PxFilterData filterData;
			filterData.word0 = shape->getSimulationFilterData().word0; // word0 = own ID

			physx::PxU32 mask;
			if (GetCollideFilterCrab())
				mask |= Physic::FilterGroup::Enum::eCRAB;
			if (GetCollideFilterPawn())
				mask |= Physic::FilterGroup::Enum::PAWN;
			if (GetCollideFilterMine())
				mask |= Physic::FilterGroup::Enum::eMINE_HEAD;
			filterData.word1 = mask;  // word1 = ID mask to filter pairs that trigger a
									  // contact callback;
			shape->setSimulationFilterData(filterData);
		}
		void SetCollideFilterMine(bool b)
		{
			mine = b;

			physx::PxFilterData filterData;
			filterData.word0 = shape->getSimulationFilterData().word0; // word0 = own ID

			physx::PxU32 mask;
			if (GetCollideFilterCrab())
				mask |= Physic::FilterGroup::Enum::eCRAB;
			if (GetCollideFilterPawn())
				mask |= Physic::FilterGroup::Enum::PAWN;
			if (GetCollideFilterMine())
				mask |= Physic::FilterGroup::Enum::eMINE_HEAD;
			filterData.word1 = mask;  // word1 = ID mask to filter pairs that trigger a
									  // contact callback;
			shape->setSimulationFilterData(filterData);
		}
		void SetCollideFilterCrab(bool b)
		{
			crab = b;

			physx::PxFilterData filterData;
			filterData.word0 = shape->getSimulationFilterData().word0; // word0 = own ID

			physx::PxU32 mask;
			if (GetCollideFilterCrab())
				mask |= Physic::FilterGroup::Enum::eCRAB;
			if (GetCollideFilterPawn())
				mask |= Physic::FilterGroup::Enum::PAWN;
			if (GetCollideFilterMine())
				mask |= Physic::FilterGroup::Enum::eMINE_HEAD;
			filterData.word1 = mask;  // word1 = ID mask to filter pairs that trigger a
									  // contact callback;
			shape->setSimulationFilterData(filterData);
		}

		CLASS_REGISTRATION()
	};

	// Wrapper PxRigidFlag
	struct QUANTIX_API RigidBodyFlag
	{
		bool					ccd = false;
		bool					ccdFriction = false;
		bool					speculativeCCD = false;
		bool					kinematic = false;
		bool					retainAcceleration = false;
		bool					useKinematicTargetForQueries = false;
		bool					poseIntegrationPreview = false;
		bool					ccdMaxContactImpulse = false;
	};

	// Wrapper PxBaseFlag
	struct QUANTIX_API BaseFlag
	{

	};

	// Wrapper PxActorFlag
	struct QUANTIX_API ActorFlag
	{
		bool					disableGravity = false;
		bool					disableSimulation = false;
		bool					sendSleepNotifies = false;
		bool					visualization = false;
	};

	// Wrapper PxShapeFlag
	struct QUANTIX_API ShapeFlag
	{
		physx::PxShape* shape { nullptr };

		bool sceneQuery = true;
		bool simulation = true;
		bool trigger = false;
		bool visualization = false;

		/**
		 * @brief Set the Shape Flag Scene Query object
		 *
		 * @param b Value of the flag
		 */
		void SetShapeFlagSceneQuery(bool b)
		{
			sceneQuery = b;
			shape->setFlag(physx::PxShapeFlag::eSCENE_QUERY_SHAPE, b);
		}

		/**
		 * @brief Get the Shape Flag Scene Query object
		 *
		 * @return true Flag is at true
		 * @return false Flag is at false
		 */
		bool GetShapeFlagSceneQuery() { return sceneQuery; };

		/**
		 * @brief Set the Shape Flag Simulation object
		 *
		 * @param b Value of the flag
		 */
		void SetShapeFlagSimulation(bool b)
		{
			simulation = b;
			shape->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, b);
		}

		/**
		 * @brief Get the Shape Flag Simulation object
		 *
		 * @return true Flag is at true
		 * @return false  Flag is at false
		 */
		bool GetShapeFlagSimulation() { return simulation; };

		/**
		 * @brief Set the Shape Flag Trigger object
		 *
		 * @param b Value of the Flag
		 */
		void SetShapeFlagTrigger(bool b)
		{
			trigger = b;
			shape->setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, b);
		}

		/**
		 * @brief Get the Shape Flag Trigger object
		 *
		 * @return true Flag is at true
		 * @return false Flag is at false
		 */
		bool GetShapeFlagTrigger() { return trigger; };

		/**
		 * @brief Set the Shape Flag Visualization object
		 *
		 * @param b Value of the Flag
		 */
		void SetShapeFlagVisualization(bool b)
		{
			visualization = b;
			shape->setFlag(physx::PxShapeFlag::eVISUALIZATION, b);
		}

		/**
		 * @brief Get the Shape Flag Visualization object
		 *
		 * @return Value of the flag
		 */
		bool GetShapeFlagVisualization() { return visualization; };

		CLASS_REGISTRATION()
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
