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

		PxRigidDynamic* _dynamic = nullptr;

#pragma endregion

	public:
#pragma region Constructors
		PhysicDynamic() noexcept;
		PhysicDynamic(PxPhysics* SDK) noexcept;
		PhysicDynamic(PxPhysics* SDK, EPhysXShape physXShape) noexcept;
		PhysicDynamic(PxPhysics* SDK, PhysicStatic* physicStatic) noexcept;
		PhysicDynamic(const PhysicDynamic&) noexcept;
		PhysicDynamic(PhysicDynamic&&) noexcept;
		~PhysicDynamic();

#pragma endregion

#pragma region Functions
		void	print();

#pragma region Operators
#pragma endregion

#pragma region Accessors
		PxRigidDynamic* GetRigid() const;
#pragma endregion
#pragma endregion
	};
}

#endif

