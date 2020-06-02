#ifndef __CONTROLLETHITREPORT_H__
#define __CONTROLLETHITREPORT_H__

#include <../characterkinematic/PxControllerBehavior.h>
#include "PxSimulationEventCallback.h"
#include <PxPhysicsAPI.h>
#include <iostream>

#include "Core/DataStructure/GameObject3D.h"
#include "Core/Components/Behaviours/Bumper.h"
#include "Core/Components/Behaviours/Killzone.h"
#include "Core/Components/CharacterController.h"

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
			Core::DataStructure::GameObject3D* other = ((Core::DataStructure::GameObject3D*)hit.actor->userData);
			if (other)
			{
				Gameplay::Bumper* bumper = other->GetComponent<Gameplay::Bumper>();
				if (bumper)
				{
					bumper->OnTrigger(other, ((Core::DataStructure::GameObject3D*)hit.controller->getUserData()));
				}
				if (other->GetLayer() == Quantix::Core::DataStructure::Layer::KILLZONE)
				{

					Core::DataStructure::GameObject3D* controllerGO = ((Core::DataStructure::GameObject3D*)hit.controller->getUserData());
					Math::QXvec3 SpawnPos = other->GetComponent<Gameplay::Killzone>()->positionToRespawnController;

					controllerGO->GetComponent<Core::Components::CharacterController>()->needSpawn = true;
					controllerGO->GetComponent<Core::Components::CharacterController>()->spawnPos = SpawnPos;
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

