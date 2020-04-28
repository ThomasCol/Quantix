#include "Physic/SimulationCallback.h"

#include "Core/DataStructure/GameObject3D.h"

#include <PxActor.h>
#include <PxRigidActorExt.h>

namespace Quantix::Physic
{
	void SimulationCallback::onConstraintBreak(PxConstraintInfo* constraints, PxU32 count)
	{
		(void*)constraints;
		(void*)count;
	}

	void SimulationCallback::onWake(PxActor** actors, PxU32 count)
	{
		(void*)actors;
		(void*)count;
	};

	void SimulationCallback::onSleep(PxActor** actors, PxU32 count)
	{
		(void*)actors;
		(void*)count;
	};


	void SimulationCallback::onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs)
	{
		for (PxU32 i = 0; i < nbPairs; i++)
		{
			const PxContactPair& cp = pairs[i];

			if (cp.events & PxPairFlag::eNOTIFY_TOUCH_FOUND)
			{
				if (pairHeader.actors[2] && pairHeader.actors[1])
				{
					((Core::DataStructure::GameObject3D*)pairHeader.actors[1]->userData)->CallOnContact((Core::DataStructure::GameObject3D*)pairHeader.actors[2]->userData);
					((Core::DataStructure::GameObject3D*)pairHeader.actors[2]->userData)->CallOnContact((Core::DataStructure::GameObject3D*)pairHeader.actors[1]->userData);
				}
			}
		}
	}

	void SimulationCallback::onTrigger(PxTriggerPair* pairs, PxU32 count)
	{
		std::cout << "OnTrigger" << std::endl;
		for (PxU32 i = 0; i < count; i++)
		{
			((Core::DataStructure::GameObject3D*)pairs->triggerActor->userData)->CallOnContact((Core::DataStructure::GameObject3D*)pairs->otherActor->userData);
		}
	}
	void SimulationCallback::onAdvance(const PxRigidBody* const* bodyBuffer, const PxTransform* poseBuffer, const PxU32 count)
	{
		(void*)bodyBuffer;
		(void*)poseBuffer;
		(void*)count;
	};
}