#ifndef __SIMULATIONCALLBACK_H__
#define __SIMULATIONCALLBACK_H__

#include <PxSimulationEventCallback.h>
#include <iostream>

using namespace physx;

namespace Quantix::Physic
{
	class SimulationCallback : public PxSimulationEventCallback
	{
	public:
		SimulationCallback() = default;
		SimulationCallback(const SimulationCallback&) = default;
		SimulationCallback(SimulationCallback&&) = default;
		~SimulationCallback() = default;

		void onConstraintBreak(PxConstraintInfo* constraints, PxU32 count) override;

		void onWake(PxActor** actors, PxU32 count) override;

		void onSleep(PxActor** actors, PxU32 count) override;

		void onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs) override;

		void onTrigger(PxTriggerPair* pairs, PxU32 count) override;
		void onAdvance(const PxRigidBody* const* bodyBuffer, const PxTransform* poseBuffer, const PxU32 count) override;
	};
}

#endif

