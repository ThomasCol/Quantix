#ifndef __CONTROLLERBEHAVIORCALLBACK_H__
#define __CONTROLLERBEHAVIORCALLBACK_H__

#include <../characterkinematic/PxControllerBehavior.h>

namespace Quantix::Physic
{
    class ControllerBehaviorCallback : public physx::PxControllerBehaviorCallback
    {
        /**
         * @brief Get the Behavior Flags object for a Contact between a controller and a shape of an actor
         * 
         * @param shape Shape who collide with the controller
         * @param actor actor who has this shape
         * @return physx::PxControllerBehaviorFlags 
         */
        physx::PxControllerBehaviorFlags		getBehaviorFlags(const physx::PxShape& shape, const physx::PxActor& actor) override;

        /**
         * @brief Get the Behavior Flags object for a contact between two controller
         * 
         * @param controller other controller
         * @return physx::PxControllerBehaviorFlags 
         */
        physx::PxControllerBehaviorFlags		getBehaviorFlags(const physx::PxController& controller) override;

        /**
         * @brief Get the Behavior Flags object for a contact between a obstacle and a controller
         * 
         * @param obstacle Obstacle who collide with the controller
         * @return physx::PxControllerBehaviorFlags 
         */
        physx::PxControllerBehaviorFlags		getBehaviorFlags(const physx::PxObstacle& obstacle) override;
    };
}
 
#endif
