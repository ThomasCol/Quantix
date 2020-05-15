#include "Physic/ControllerBehaviorCallback.h"
#include <iostream>


using namespace physx;
namespace Quantix::Physic
{
	physx::PxControllerBehaviorFlags ControllerBehaviorCallback::getBehaviorFlags(const physx::PxShape& shape, const physx::PxActor& actor)
	{
		return physx::PxControllerBehaviorFlag::eCCT_CAN_RIDE_ON_OBJECT;
	}

	physx::PxControllerBehaviorFlags		ControllerBehaviorCallback::getBehaviorFlags(const physx::PxController& controller)
	{ 
		return physx::PxControllerBehaviorFlag::eCCT_CAN_RIDE_ON_OBJECT; 
	}

	physx::PxControllerBehaviorFlags		ControllerBehaviorCallback::getBehaviorFlags(const physx::PxObstacle& obstacle)
	{ 
		return PxControllerBehaviorFlag::eCCT_CAN_RIDE_ON_OBJECT | PxControllerBehaviorFlag::eCCT_SLIDE;
	}
}