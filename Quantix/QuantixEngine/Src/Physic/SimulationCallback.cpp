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
					PxContactPairPoint buffer[1];
					pairs[i].extractContacts(buffer, 1);
					Math::QXvec3 normal = Math::QXvec3(buffer[0].normal.x, buffer[0].normal.y, buffer[0].normal.z);
					Math::QXvec3 position = Math::QXvec3(buffer[0].position.x, buffer[0].position.y, buffer[0].position.z);

					// Call OnContact Function of each GameObject
					((Core::DataStructure::GameObject3D*)pairHeader.actors[1]->userData)->CallOnContact((Core::DataStructure::GameObject3D*)pairHeader.actors[2]->userData, position, normal);
					((Core::DataStructure::GameObject3D*)pairHeader.actors[2]->userData)->CallOnContact((Core::DataStructure::GameObject3D*)pairHeader.actors[1]->userData, position, normal);
				}
			}
		}
	}

	void SimulationCallback::onTrigger(PxTriggerPair* pairs, PxU32 count)
	{
		for (PxU32 i = 0; i < count; i++)
		{
			// Call OnTrigger Function of GameObject who is trigger
			((Core::DataStructure::GameObject3D*)pairs[i].triggerActor->userData)->CallOnTrigger((Core::DataStructure::GameObject3D*)pairs[i].otherActor->userData);
		}
	}

	void SimulationCallback::onAdvance(const PxRigidBody* const* bodyBuffer, const PxTransform* poseBuffer, const PxU32 count)
	{
		(void*)bodyBuffer;
		(void*)poseBuffer;
		(void*)count;
	};
}