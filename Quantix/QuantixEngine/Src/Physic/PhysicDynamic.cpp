#include "Physic/PhysicDynamic.h"

#include <iostream>
#include "Physic/PhysicStatic.h"
#include <PxRigidActorExt.h>

RTTR_PLUGIN_REGISTRATION
{
	rttr::registration::class_<Quantix::Physic::PhysicDynamic>("PhysicDynamic")
	.constructor<>()
	.constructor<physx::PxPhysics*>()
	.constructor<physx::PxPhysics*, Quantix::Physic::EPhysXShape>()
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
		_dynamic = SDK->createRigidDynamic(PxTransform(PxVec3(0, 2, 0)));

		PxMaterial* aMaterial = SDK->createMaterial(0.5f, 0.5f, 0.1f);

		PxShape* aCubeShape = SDK->createShape(PxBoxGeometry(0.5f, 0.5f, 0.5f), *aMaterial);
		std::cout << "Dynamic ==> position: {" << _dynamic->getGlobalPose().p.x << ", " << _dynamic->getGlobalPose().p.y << ", " << _dynamic->getGlobalPose().p.z << "}" << std::endl;
		_dynamic->attachShape(*aCubeShape);
		PxRigidBodyExt::updateMassAndInertia(*_dynamic, 0.5f);
	}

	PhysicDynamic::PhysicDynamic(PxPhysics* SDK, EPhysXShape physXShape) noexcept : IPhysicType(ETypePhysic::DYNAMIC)
	{
		if (type != ETypePhysic::NONE)
			std::cout << "type set: Dynamic" << std::endl;

		_dynamic = SDK->createRigidDynamic(PxTransform(PxVec3(0, 10, 0)));
		//_dynamic->setRigidBodyFlag(PxRigidBodyFlag::eENABLE_CCD, true);
		//_dynamic->setRigidBodyFlag(PxRigidBodyFlag::, true);

		PxMaterial* aMaterial = SDK->createMaterial(1.f, 1.f, 1.f);
		PxShape* aShape = nullptr;

		if (physXShape == EPhysXShape::CUBE)
		{
			aShape = SDK->createShape(PxBoxGeometry(1.f, 1.f, 1.f), *aMaterial);
			aShape->setFlag(PxShapeFlag::eSCENE_QUERY_SHAPE, true);
			aShape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, true);
			std::cout << "shape: Cube" << std::endl;
		}
		else if (physXShape == EPhysXShape::SPHERE)
		{
			aShape = SDK->createShape(PxSphereGeometry(1.f), *aMaterial);
			aShape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
			aShape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);
			std::cout << "shape: Sphere" << std::endl;
		}
		else if (physXShape == EPhysXShape::CAPSULE)
		{
			aShape = SDK->createShape(PxCapsuleGeometry(1.f, 1.f), *aMaterial);
			aShape->setFlag(PxShapeFlag::eSCENE_QUERY_SHAPE, true);
			aShape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, true);
			std::cout << "shape: Capsule" << std::endl;
		}
		std::cout << "Dynamic ==> position: {" << _dynamic->getGlobalPose().p.x << ", " << _dynamic->getGlobalPose().p.y << ", " << _dynamic->getGlobalPose().p.z << "}" << std::endl;
		_dynamic->attachShape(*aShape);
		PxRigidBodyExt::updateMassAndInertia(*_dynamic, 1.f);
	}

	PhysicDynamic::PhysicDynamic(PxPhysics* SDK, PhysicStatic* physicStatic) noexcept
	{
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

	void PhysicDynamic::print()
	{
		std::cout << "Je suis dynamic" << std::endl;
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