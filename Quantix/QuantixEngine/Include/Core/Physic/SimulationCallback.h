#ifndef __SIMULATIONCALLBACK_H__
#define __SIMULATIONCALLBACK_H__

#include <PxSimulationEventCallback.h>
#include <iostream>

using namespace physx;

namespace Quantix::Core::Physic
{
	class SimulationCallback : public PxSimulationEventCallback
	{
	public:

#pragma region Constructors
		/**
		 * @brief Construct a new Simulation Callback object
		 * 
		 */
		SimulationCallback() = default;

		/**
		 * @brief Construct a new Simulation Callback object
		 * 
		 * @param src SimulationCallback to copy
		 */
		SimulationCallback(const SimulationCallback& src) = default;

		/**
		 * @brief Construct a new Simulation Callback object
		 * 
		 * @param src SimulationCallback to move
		 */
		SimulationCallback(SimulationCallback&& src) = default;

		/**
		 * @brief Destroy the Simulation Callback object
		 * 
		 */
		~SimulationCallback() = default;

#pragma endregion

		/**
		 * @brief Function call when a constraint is break
		 * 
		 * @param constraints Info on Constraint broke
		 * @param count number of constraints broke
		 */
		void onConstraintBreak(PxConstraintInfo* constraints, PxU32 count) override;

		/**
		 * @brief Function Call when an actorphysic is awake
		 * 
		 * @param actors List of Actor awake
		 * @param count Number of actor awake
		 */
		void onWake(PxActor** actors, PxU32 count) override;

		/**
		 * @brief Function Call when an actorphysic is sleeping
		 * 
		 * @param actors List of Actor sleep
		 * @param count Number of actor sleeping
		 */
		void onSleep(PxActor** actors, PxU32 count) override;

		/**
		 * @brief Function Call when Physic raise a collision
		 * 
		 * @param pairHeader header of pairs
		 * @param pairs List of pairs
		 * @param nbPairs number of pair
		 */
		void onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs) override;

		/**
		 * @brief Function call when Physic raise a trigger enter
		 * 
		 * @param pairs List of pair
		 * @param count Number of pair in the list
		 */
		void onTrigger(PxTriggerPair* pairs, PxU32 count) override;

		void onAdvance(const PxRigidBody* const* bodyBuffer, const PxTransform* poseBuffer, const PxU32 count) override;
	};
}

#endif

