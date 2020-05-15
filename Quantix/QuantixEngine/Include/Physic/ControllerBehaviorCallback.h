#ifndef __CONTROLLERBEHAVIORCALLBACK_H__
#define __CONTROLLERBEHAVIORCALLBACK_H__

#include <../characterkinematic/PxControllerBehavior.h>

namespace Quantix::Physic
{
    class ControllerBehaviorCallback : public physx::PxControllerBehaviorCallback
    {
        physx::PxControllerBehaviorFlags		getBehaviorFlags(const physx::PxShape& shape, const physx::PxActor& actor) override;

        physx::PxControllerBehaviorFlags		getBehaviorFlags(const physx::PxController& controller) override;

        physx::PxControllerBehaviorFlags		getBehaviorFlags(const physx::PxObstacle& obstacle) override;
    };
}
 
#endif
