#ifndef __IPHYSICTYPE_H__
#define __IPHYSICTYPE_H__

//#include <PxActor.h>
//#include <PxPhysicsAPI.h>
//#include <PxRigidActorExt.h>

namespace Physic
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
		ETypePhysic		type = ETypePhysic::NONE;

	public:
		IPhysicType() noexcept;
		IPhysicType(ETypePhysic oType) noexcept;
		IPhysicType(const IPhysicType&) noexcept;
		IPhysicType(IPhysicType&&) noexcept;
		virtual ~IPhysicType() = default;

		void		print();

		ETypePhysic		GetType();
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
	};
}

#endif

