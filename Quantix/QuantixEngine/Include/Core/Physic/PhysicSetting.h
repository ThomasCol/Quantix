#ifndef __PHYSICSETTING_H__
#define __PHYSICSETTING_H__

#include "Core/DLLHeader.h"
#include "rttrEnabled.h"
#include "Core/Physic/PhysicDynamic.h"

namespace Quantix::Core::Physic
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
		QXbool pawn = QX_TRUE;
		QXbool mine = QX_TRUE;
		QXbool crab = QX_TRUE;
	};

	// Wrapper PxRigidFlag
	struct QUANTIX_API RigidBodyFlag
	{
		QXbool					ccd = QX_FALSE;
		QXbool					ccdFriction = QX_FALSE;
		QXbool					speculativeCCD = QX_FALSE;
		QXbool					kinematic = QX_FALSE;
		QXbool					retainAcceleration = QX_FALSE;
		QXbool					useKinematicTargetForQueries = QX_FALSE;
		QXbool					poseIntegrationPreview = QX_FALSE;
		QXbool					ccdMaxContactImpulse = QX_FALSE;
	};

	// Wrapper PxRigidLockFlag
	struct QUANTIX_API RigidBodyLockFlag
	{
		QXbool					lockLinearX = QX_FALSE;
		QXbool					lockLinearY = QX_FALSE;
		QXbool					lockLinearZ = QX_FALSE;
		QXbool					lockAngularX = QX_FALSE;
		QXbool					lockAngularY = QX_FALSE;
		QXbool					lockAngularZ = QX_FALSE;
	};

	// Wrapper PxBaseFlag
	struct QUANTIX_API BaseFlag
	{

	};

	// Wrapper PxActorFlag
	struct QUANTIX_API ActorFlag
	{
		QXbool					disableGravity = QX_FALSE;
		QXbool					disableSimulation = QX_FALSE;
		QXbool					sendSleepNotifies = QX_FALSE;
		QXbool					visualization = QX_FALSE;
	};

	// Wrapper PxShapeFlag
	struct QUANTIX_API ShapeFlag
	{
		QXbool sceneQuery = QX_TRUE;
		QXbool simulation = QX_TRUE;
		QXbool trigger = QX_FALSE;
		QXbool visualization = QX_FALSE;
	};

	// Wrapper PxSceneFlag
	struct QUANTIX_API SceneFlag
	{
		QXbool adaptiveForce = QX_FALSE;
		QXbool disableCCDResweep = QX_FALSE;
		QXbool disableContactCache = QX_FALSE;
		QXbool disableContactReportResize = QX_FALSE;
		QXbool activeActors = QX_TRUE;
		QXbool averagePoint = QX_FALSE;
		QXbool ccd = QX_FALSE;
		QXbool enhancedDeterminism = QX_FALSE;
		QXbool frictionEveryIteration = QX_FALSE;
		QXbool gpuDynamics = QX_FALSE;
		QXbool pcm = QX_FALSE;
		QXbool stabilization = QX_FALSE;
		QXbool excludeKineActiveActors = QX_FALSE;
		QXbool mutableFlags = QX_FALSE;
		QXbool requireRWLock = QX_FALSE;
	};
}

#endif // !__PHYSICSETTING_H__
