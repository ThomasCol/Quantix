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
		PhysicStatic() noexcept;

		/**
		 * @brief Construct a new Physic Static object
		 * 
		 * @param SDK PxPhysic
		 */
		PhysicStatic(PxPhysics* SDK) noexcept;

		/**
		 * @brief Construct a new Physic Static object
		 * 
		 * @param SDK PxPhysic
		 * @param physicDynamic Actor Dynamic to switch in Static
		 */
		PhysicStatic(PxPhysics* SDK, PhysicDynamic* physicDynamic) noexcept;

		/**
		 * @brief Construct a new Physic Static object
		 * 
		 * @param src Physicstatic to copy
		 */
		PhysicStatic(const PhysicStatic& src) noexcept;

		/**
		 * @brief Construct a new Physic Static object
		 * 
		 * @param src Physicstatic to move
		 */
		PhysicStatic(PhysicStatic&& src) noexcept;

		/**
		 * @brief Destroy the Physic Static object
		 * 
		 */
		~PhysicStatic() noexcept;
#pragma endregion

#pragma region Functions
#pragma region Accessors

		/**
		 * @brief Get the Rigid object
		 * 
		 * @return PxRigidStatic* pointer on rigid
		 */
		PxRigidStatic* GetRigid() noexcept;

		/**
		 * @brief Set the Rigid object
		 * 
		 * @param rigid New value of rigid
		 */
		void SetRigid(PxRigidStatic* rigid) noexcept;
		
#pragma endregion
#pragma endregion
		CLASS_REGISTRATION(Quantix::Physic::IPhysicType)
	};
}
#endif

