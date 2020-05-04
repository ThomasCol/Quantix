#ifndef __PHYSICDYNAMIC_H__
#define __PHYSICDYNAMIC_H__

#include "Physic/IPhysicType.h"
#include "Physic/Transform3D.h"

namespace Quantix::Physic
{
	using namespace physx;

	class PhysicStatic;

	class PhysicDynamic : public IPhysicType
	{
	private:
#pragma region Attributes

		// Actor PhysX
		PxRigidDynamic* _dynamic = nullptr;

#pragma endregion

	public:
#pragma region Constructors

		/**
		 * @brief Construct a new Physic Dynamic object
		 * 
		 */
		PhysicDynamic() noexcept;

		/**
		 * @brief Construct a new Physic Dynamic object
		 * 
		 * @param SDK PxScene
		 */
		PhysicDynamic(PxPhysics* SDK) noexcept;

		/**
		 * @brief Construct a new Physic Dynamic object
		 * 
		 * @param SDK PxScene
		 * @param physicStatic PhysicStatic to Switch 
		 */
		PhysicDynamic(PxPhysics* SDK, PhysicStatic* physicStatic) noexcept;

		/**
		 * @brief Construct a new Physic Dynamic object
		 * 
		 * @param src PhysicDynamic to copy
		 */
		PhysicDynamic(const PhysicDynamic& src) noexcept;

		/**
		 * @brief Construct a new Physic Dynamic object
		 * 
		 * @param src PhysicDynamic to Move
		 */
		PhysicDynamic(PhysicDynamic&& src) noexcept;

		/**
		 * @brief Destroy the Physic Dynamic object
		 * 
		 */
		~PhysicDynamic();

#pragma endregion

#pragma region Functions
#pragma region Operators
#pragma endregion

#pragma region Accessors

		/**
		 * @brief Get the Rigid object
		 * 
		 * @return PxRigidDynamic* Pointer on the rigid
		 */
		PxRigidDynamic* GetRigid();

		/**
		 * @brief Set the Rigid object
		 * 
		 * @param rigid new Value of rigid
		 */
		void SetRigid(PxRigidDynamic* rigid);
		
#pragma endregion
#pragma endregion

		CLASS_REGISTRATION(Quantix::Physic::IPhysicType)
	};
}

#endif

