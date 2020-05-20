#ifndef __CONTROLLETHITREPORT_H__
#define __CONTROLLETHITREPORT_H__

#include <../characterkinematic/PxControllerBehavior.h>
#include "PxSimulationEventCallback.h"
#include <PxPhysicsAPI.h>
#include <iostream>

#include "Core/DataStructure/GameObject3D.h"

namespace Quantix::Physic
{
	class ControllerHitReport : public physx::PxUserControllerHitReport
	{
		/**
		 * @brief Called when Physic raise a collision between a shape and a controller
		 * 
		 * @param hit Information of hit
		 */
		virtual void							onShapeHit(const physx::PxControllerShapeHit& hit) 
		{
			Core::DataStructure::GameObject3D* object = ((Core::DataStructure::GameObject3D*)hit.actor->userData);
			if (object) 
			{
				if (object->GetLayer() == Quantix::Core::DataStructure::Layer::KILLZONE)
				{
					Core::DataStructure::GameObject3D* object = ((Core::DataStructure::GameObject3D*)hit.controller->getUserData());
					object->Destroy();
				}
			}
		};

		/**
		 * @brief called when Physic raise a collision between two controller
		 * 
		 * @param hit information of hit
		 */
		virtual void							onControllerHit(const physx::PxControllersHit& hit) {}

		/**
		 * @brief called when Physic raise a collision between an obstacle and a controller
		 * 
		 * @param hit information of hit
		 */
		virtual void							onObstacleHit(const physx::PxControllerObstacleHit& hit) {}
	};
}
#endif

