#ifndef __IPHYSICTYPE_H__
#define __IPHYSICTYPE_H__


#include <PxActor.h>

#include <PxPhysicsAPI.h>
#include <PxRigidActorExt.h>

#include "rttrEnabled.h"

namespace Quantix::Physic
{
	class PhysicStatic;
	class PhysicDynamic;

	enum class	EPhysXShape
	{
		CUBE,
		SPHERE,
		CAPSULE
	};

	enum class ETypePhysic
	{
		STATIC,
		DYNAMIC,
		NONE
	};

	class IPhysicType
	{
	protected:
#pragma region Attributes
		// To know if PxActor is static or Dynamic
		ETypePhysic		type = ETypePhysic::NONE;
#pragma endregion
	public:

#pragma region Constructors	

		/**
		 * @brief Construct a new IPhysicType object
		 * 
		 */
		IPhysicType() noexcept;

		/**
		 * @brief Construct a new IPhysicType object
		 * 
		 * @param oType type Value
		 */
		IPhysicType(ETypePhysic oType) noexcept;

		/**
		 * @brief Construct a new IPhysicType object
		 * 
		 * @param src IPhysicType to Copy
		 */
		IPhysicType(const IPhysicType& src) noexcept;

		/**
		 * @brief Construct a new IPhysicType object
		 * 
		 * @param src IPhysicType to move
		 */
		IPhysicType(IPhysicType&& src) noexcept;

		/**
		 * @brief Destroy the IPhysicType object
		 * 
		 */
		virtual ~IPhysicType() = default;
#pragma endregion

#pragma region Functions
#pragma region Accessors

		/**
		 * @brief Get the Type object
		 * 
		 * @return ETypePhysic& Value of type
		 */
		ETypePhysic&		GetType() noexcept;

		/**
		 * @brief Set the Type object
		 * 
		 * @param nt new value of type
		 */
		void		SetType(ETypePhysic& nt) noexcept { type = nt; };
		
		/**
		 * @brief Get the IPhysicType object
		 * 
		 * @tparam T type of the IPhysicType
		 * @return T* Object IPhysictype
		 */
		template<class T>
		T* GetObject() noexcept
		{
			if (type == ETypePhysic::STATIC)
				return (dynamic_cast<PhysicStatic*>(this));
			else if (type == ETypePhysic::DYNAMIC)
				return (dynamic_cast<PhysicDynamic*>(this));
		}

		/**
		 * @brief Get the Object Dynamic object
		 * 
		 * @return PhysicDynamic* Pointer on PhysicDynamic
		 */ 
		PhysicDynamic* GetObjectDynamic() noexcept
		{
			return (PhysicDynamic*)this;
		}

		/**
		 * @brief Get the Object Static object
		 * 
		 * @return PhysicStatic* Pointer on PhysicStatic
		 */
		PhysicStatic* GetObjectStatic() noexcept
		{
			return (PhysicStatic*)this;
		}
#pragma endregion
#pragma endregion
		CLASS_REGISTRATION()
	};
}

#endif

