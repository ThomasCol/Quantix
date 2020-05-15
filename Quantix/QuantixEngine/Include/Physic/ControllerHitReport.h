#ifndef __CONTROLLETHITREPORT_H__
#define __CONTROLLETHITREPORT_H__

#include <../characterkinematic/PxControllerBehavior.h>
#include "PxSimulationEventCallback.h"
#include <PxPhysicsAPI.h>
namespace Quantix::Physic
{
	class ControllerHitReport : public physx::PxUserControllerHitReport
	{
		virtual void							onShapeHit(const physx::PxControllerShapeHit& hit) {};

		virtual void							onControllerHit(const physx::PxControllersHit& hit) {}

		virtual void							onObstacleHit(const physx::PxControllerObstacleHit& hit) {}
	};
}
#endif
