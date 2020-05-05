#ifndef __PHYSICSETTING_H__
#define __PHYSICSETTING_H__

#include "Core/DLLHeader.h"
#include "rttrEnabled.h"

namespace Quantix::Physic
{
	// Wrapper PxRigidFlag
	struct QUANTIX_API RigidBodyFlag
	{
		bool ccd = false;
		bool ccdFriction = false;
		bool speculativeCCD = false;
		bool kinematic = false;
		bool retainAcceleration = false;
		bool useKinematicTargetForQueries = false;
		bool poseIntegrationPreview = false;
		bool ccdMaxContactImpulse = false;
	};

	// Wrapper PxBaseFlag
	struct QUANTIX_API BaseFlag
	{

	};

	// Wrapper PxActorFlag
	struct QUANTIX_API ActorFlag
	{
		bool disableGravity = false;
		bool disableSimulation = false;
		bool sendSleepNotifies = false;
		bool visualization = false;

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
