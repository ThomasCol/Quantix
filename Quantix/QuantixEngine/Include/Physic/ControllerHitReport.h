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

		virtual void							onControllerHit(const physx::PxControllersHit& hit) {}

		virtual void							onObstacleHit(const physx::PxControllerObstacleHit& hit) {}
	};
}
#endif

