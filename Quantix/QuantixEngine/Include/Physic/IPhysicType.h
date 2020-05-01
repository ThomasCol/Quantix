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
		IPhysicType() noexcept;
		IPhysicType(ETypePhysic oType) noexcept;
		IPhysicType(const IPhysicType&) noexcept;
		IPhysicType(IPhysicType&&) noexcept;
		virtual ~IPhysicType() = default;
#pragma endregion

#pragma region Functions
#pragma region Accessors
		ETypePhysic&		GetType();
		void		SetType(ETypePhysic& nt) { type = nt; };
		
		template<class T>
		T* GetObject()
		{
			if (type == ETypePhysic::STATIC)
				return (dynamic_cast<PhysicStatic*>(this));
			else if (type == ETypePhysic::DYNAMIC)
				return (dynamic_cast<PhysicDynamic*>(this));
		}

		PhysicDynamic* GetObjectDynamic()
		{
			return (PhysicDynamic*)this;
		}

		PhysicStatic* GetObjectStatic()
		{
			return (PhysicStatic*)this;
		}
#pragma endregion
#pragma endregion
		CLASS_REGISTRATION()
	};
}

#endif

