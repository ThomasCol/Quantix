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

	enum class NonWalkableMode
	{
		PREVENTCLIMBING,
		PREVENTCLIMBINGANDFORCESLIDING
	};

	enum class ClimbingMode
	{
		CONSTRAINED,
		EASY,
		LAST
	};

	// Different way to apply a force
	enum class ForceMode
	{
		ACCELERATION,
		IMPULSE,
		VELOCITYCHANGE,
		FORCE
	};

	struct QUANTIX_API CollideGroup
	{
		bool pawn = true;
		bool mine = true;
		bool crab = true;
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

	// Wrapper PxRigidLockFlag
	struct QUANTIX_API RigidBodyLockFlag
	{
		bool					lockLinearX = false;
		bool					lockLinearY = false;
		bool					lockLinearZ = false;
		bool					lockAngularX = false;
		bool					lockAngularY = false;
		bool					lockAngularZ = false;
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
