#ifndef __CONTROLLERBEHAVIORCALLBACK_H__
#define __CONTROLLERBEHAVIORCALLBACK_H__

#include <../characterkinematic/PxControllerBehavior.h>

namespace Quantix::Physic
{
    class ControllerBehaviorCallback : public physx::PxControllerBehaviorCallback
    {
        virtual physx::PxControllerBehaviorFlags		getBehaviorFlags(const physx::PxShape& shape, const physx::PxActor& actor) { return physx::PxControllerBehaviorFlag::eCCT_CAN_RIDE_ON_OBJECT; };

        virtual physx::PxControllerBehaviorFlags		getBehaviorFlags(const physx::PxController& controller) { return physx::PxControllerBehaviorFlag::eCCT_CAN_RIDE_ON_OBJECT; };

        virtual physx::PxControllerBehaviorFlags		getBehaviorFlags(const physx::PxObstacle& obstacle) { return physx::PxControllerBehaviorFlag::eCCT_CAN_RIDE_ON_OBJECT; };
    };
}
 
#endif
