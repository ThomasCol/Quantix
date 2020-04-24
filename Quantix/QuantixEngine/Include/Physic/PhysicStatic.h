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
		PxRigidStatic* _static = nullptr;
#pragma endregion
	public:
#pragma region Constructors
		PhysicStatic();
		PhysicStatic(PxPhysics* SDK);
		PhysicStatic(PxPhysics* SDK, EPhysXShape physXShape);
		PhysicStatic(PxPhysics* SDK, PhysicDynamic* physicDynamic);
		PhysicStatic(const PhysicStatic&);
		PhysicStatic(PhysicStatic&&);
		~PhysicStatic();
#pragma endregion

#pragma region Functions
		void	print();

		PxRigidStatic* GetRigid();
		void SetRigid(PxRigidStatic* rigid);
#pragma endregion
		CLASS_REGISTRATION(Quantix::Physic::IPhysicType)
	};
}
#endif

