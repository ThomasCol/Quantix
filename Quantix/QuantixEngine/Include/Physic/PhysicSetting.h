#ifndef __PHYSICSETTING_H__
#define __PHYSICSETTING_H__

#include "Core/DLLHeader.h"
#include "rttrEnabled.h"

namespace Quantix::Physic
{
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

	struct QUANTIX_API BaseFlag
	{

	};

	struct QUANTIX_API ActorFlag
	{
		bool disableGravity = false;
		bool disableSimulation = false;
		bool sendSleepNotifies = false;
		bool visualization = false;

		CLASS_REGISTRATION()
	};

	struct QUANTIX_API ShapeFlag
	{
		bool sceneQuery = true;
		bool simulation = true;
		bool trigger = false;
		bool visualization = false;
	};
}

#endif // !__PHYSICSETTING_H__
