#include "Physic/SimulationCallback.h"

#include "Core/DataStructure/GameObject3D.h"

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
		std::cout << "OnContact" << std::endl;
		std::cout << nbPairs << std::endl;

		for (PxU32 i = 0; i < nbPairs; i++)
		{
			const PxContactPair& cp = pairs[i];

			if (cp.events & PxPairFlag::eNOTIFY_TOUCH_FOUND)
			{
				std::cout << "BOOM" << std::endl;
			}
		}
	}

	void SimulationCallback::onTrigger(PxTriggerPair* pairs, PxU32 count)
	{
		std::cout << "OnTrigger" << std::endl;
		for (PxU32 i = 0; i < count; i++)
		{
			//dynamic_cast<GameObject*>(pairs->triggerActor->userData)->OnTriggerEnter()
			// ignore pairs when shapes have been deleted
			//if (pairs[i].flags & (PxTriggerPairFlag::eREMOVED_SHAPE_TRIGGER | PxTriggerPairFlag::eREMOVED_SHAPE_OTHER))
				//continue;
		}
	}
	void SimulationCallback::onAdvance(const PxRigidBody* const* bodyBuffer, const PxTransform* poseBuffer, const PxU32 count)
	{
		(void*)bodyBuffer;
		(void*)poseBuffer;
		(void*)count;
	};
}