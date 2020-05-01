#include "Physic/PhysicDynamic.h"

#include <iostream>
#include "Physic/PhysicStatic.h"
#include <PxRigidActorExt.h>

RTTR_PLUGIN_REGISTRATION
{
	rttr::registration::class_<Quantix::Physic::PhysicDynamic>("PhysicDynamic")
	.constructor<>()
	.constructor<physx::PxPhysics*>()
	.constructor<physx::PxPhysics*, Quantix::Physic::PhysicStatic*>()
	.constructor<const Quantix::Physic::PhysicDynamic&>()
	.constructor<Quantix::Physic::PhysicDynamic&&>()
	.enumeration<Quantix::Physic::EPhysXShape>("EPhysXShape")
					 (rttr::value("Cube", Quantix::Physic::EPhysXShape::CUBE),
					 rttr::value("Sphere", Quantix::Physic::EPhysXShape::SPHERE),
					 rttr::value("Capsule", Quantix::Physic::EPhysXShape::CAPSULE))
	.property("dynamic", &Quantix::Physic::PhysicDynamic::GetRigid, &Quantix::Physic::PhysicDynamic::SetRigid);
}

namespace Quantix::Physic
{
	using namespace physx;
	PhysicDynamic::PhysicDynamic() noexcept : IPhysicType(ETypePhysic::DYNAMIC)
	{
		if (type != ETypePhysic::NONE)
			std::cout << "type set: Dynamic" << std::endl;
	}

	PhysicDynamic::PhysicDynamic(PxPhysics* SDK) noexcept : IPhysicType(ETypePhysic::DYNAMIC)
	{
		if (type != ETypePhysic::NONE)
			std::cout << "type set: Dynamic" << std::endl;

		// Create ActorPhysic Dynamic
		_dynamic = SDK->createRigidDynamic(PxTransform(PxVec3(0, 2, 0)));
	}

	PhysicDynamic::PhysicDynamic(PxPhysics* SDK, PhysicStatic* physicStatic) noexcept
	{
		// Set Type
		type = ETypePhysic::DYNAMIC;

		int nb = physicStatic->GetRigid()->getNbShapes();
		PxShape* shape;
		physicStatic->GetRigid()->getShapes(&shape, nb);

		// Prendre les valeurs du static
		_dynamic = SDK->createRigidDynamic(PxTransform(physicStatic->GetRigid()->getGlobalPose()));

		std::cout << "nb of shape : " << nb << std::endl;
		for (int i = 0; i < nb; i++)
		{
			std::cout << "attach one shape" << std::endl;
			_dynamic->attachShape(shape[i]);
			physicStatic->GetRigid()->detachShape(shape[i]);
		}
		Core::DataStructure::GameObject3D* data = (Core::DataStructure::GameObject3D*)physicStatic->GetRigid()->userData;
		_dynamic->userData = data;
		PxRigidBodyExt::updateMassAndInertia(*_dynamic, 1.f);
	}

	PhysicDynamic::PhysicDynamic(const PhysicDynamic& pd) noexcept : IPhysicType(pd)
	{
		_dynamic = pd._dynamic;
	}

	PhysicDynamic::PhysicDynamic(PhysicDynamic&& pd) noexcept : IPhysicType(pd)
	{
		type = std::move(pd.type);
		_dynamic = std::move(pd._dynamic);
	}

	PhysicDynamic::~PhysicDynamic()
	{
	}

	PxRigidDynamic* PhysicDynamic::GetRigid()
	{
		return _dynamic;
	}

	void PhysicDynamic::SetRigid(PxRigidDynamic* rigid)
	{
		_dynamic = rigid;
	}
}