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

namespace Quantix::Core::Physic
{
	class ControllerHitReport : public physx::PxUserControllerHitReport
	{
		/**
		 * @brief Called when Physic raise a collision between a shape and a controller
		 * 
		 * @param hit Information of hit
		 */
		virtual void							onShapeHit(const physx::PxControllerShapeHit& hit) override
		{
			Core::DataStructure::GameObject3D* other = ((Core::DataStructure::GameObject3D*)hit.actor->userData);
			if (other)
			{
				Core::Components::Behaviours::Bumper* bumper = other->GetComponent<Core::Components::Behaviours::Bumper>();

				// Controller Collide with a Bumper
				if (bumper)
					bumper->OnTrigger(other, ((Core::DataStructure::GameObject3D*)hit.controller->getUserData()));

				// Controller Collide with a Killzone
				if (other->GetLayer() == Quantix::Core::DataStructure::Layer::KILLZONE)
				{
					Core::DataStructure::GameObject3D* controllerGO = ((Core::DataStructure::GameObject3D*)hit.controller->getUserData());

					// Teleport the controller at the Position of spawn found in the killzone
					controllerGO->GetComponent<Core::Components::CharacterController>()->needSpawn = true;
					controllerGO->GetComponent<Core::Components::CharacterController>()->spawnPos = other->GetComponent<Core::Components::Behaviours::Killzone>()->positionToRespawnController;
				}
			}
		};

		/**
		 * @brief called when Physic raise a collision between two controller
		 * 
		 * @param hit information of hit
		 */
		virtual void							onControllerHit(const physx::PxControllersHit& hit) override {}

		/**
		 * @brief called when Physic raise a collision between an obstacle and a controller
		 * 
		 * @param hit information of hit
		 */
		virtual void							onObstacleHit(const physx::PxControllerObstacleHit& hit) {}
	};
}
#endif

