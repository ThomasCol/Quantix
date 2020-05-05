#ifndef __PHYSICSTATIC_H__
#define __PHYSICSTATIC_H__

#include <iostream>
#include <PxPhysicsAPI.h>

#include "Physic/IPhysicType.h"

namespace Quantix::Physic
{
	using namespace physx;
	class PhysicStatic : public IPhysicType
	{
	private:
#pragma region Attributes
		// Actor Physic
		PxRigidStatic* _static = nullptr;
#pragma endregion
	public:
#pragma region Constructors

		/**
		 * @brief Construct a new Physic Static object
		 * 
		 */
		PhysicStatic();

		/**
		 * @brief Construct a new Physic Static object
		 * 
		 * @param SDK PxPhysic
		 */
		PhysicStatic(PxPhysics* SDK);

		/**
		 * @brief Construct a new Physic Static object
		 * 
		 * @param SDK PxPhysic
		 * @param physicDynamic Actor Dynamic to switch in Static
		 */
		PhysicStatic(PxPhysics* SDK, PhysicDynamic* physicDynamic);

		/**
		 * @brief Construct a new Physic Static object
		 * 
		 * @param src Physicstatic to copy
		 */
		PhysicStatic(const PhysicStatic& src);

		/**
		 * @brief Construct a new Physic Static object
		 * 
		 * @param src Physicstatic to move
		 */
		PhysicStatic(PhysicStatic&& src);

		/**
		 * @brief Destroy the Physic Static object
		 * 
		 */
		~PhysicStatic();
#pragma endregion

#pragma region Functions
#pragma region Accessors

		/**
		 * @brief Get the Rigid object
		 * 
		 * @return PxRigidStatic* pointer on rigid
		 */
		PxRigidStatic* GetRigid();

		/**
		 * @brief Set the Rigid object
		 * 
		 * @param rigid New value of rigid
		 */
		void SetRigid(PxRigidStatic* rigid);
		
#pragma endregion
#pragma endregion
		CLASS_REGISTRATION(Quantix::Physic::IPhysicType)
	};
}
#endif

