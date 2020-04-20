#include "Physic/PhysicStatic.h"
#include "Physic/PhysicDynamic.h"

namespace Quantix::Physic
{
	PhysicStatic::PhysicStatic() : IPhysicType(ETypePhysic::STATIC)
	{
		if (type != ETypePhysic::NONE)
			std::cout << "type set: Static" << std::endl;
	}

	PhysicStatic::PhysicStatic(PxPhysics* SDK) : IPhysicType(ETypePhysic::STATIC)
	{
		if (type != ETypePhysic::NONE)
			std::cout << "type set: Static" << std::endl;

		_static = SDK->createRigidStatic(PxTransform(PxVec3(0, -2, 0)));

		PxMaterial* aMaterial = SDK->createMaterial(0.5f, 0.5f, 0.1f);

		PxShape* aCubeShape = SDK->createShape(PxBoxGeometry(0.5f, 0.5f, 0.5f), *aMaterial);
		_static->attachShape(*aCubeShape);
	}

	PhysicStatic::PhysicStatic(PxPhysics* SDK, EPhysXShape physXShape)
	{
		if (type != ETypePhysic::NONE)
			std::cout << "type set: Static" << std::endl;

		_static = SDK->createRigidStatic(PxTransform(PxVec3(0, -1, 0)));

		PxMaterial* aMaterial = SDK->createMaterial(0.5f, 0.5f, 0.1f);
		PxShape* aShape = nullptr;

		if (physXShape == EPhysXShape::CUBE)
		{
			aShape = SDK->createShape(PxBoxGeometry(1000.f, 1.f, 1000.f), *aMaterial);
			aShape->setFlag(PxShapeFlag::eSCENE_QUERY_SHAPE, true);
			aShape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, true);
			std::cout << "shape: Cube" << std::endl;
		}
		else if (physXShape == EPhysXShape::SPHERE)
		{
			aShape = SDK->createShape(PxSphereGeometry(1.f), *aMaterial);
			std::cout << "shape: Sphere" << std::endl;
		}
		else if (physXShape == EPhysXShape::CAPSULE)
		{
			aShape = SDK->createShape(PxCapsuleGeometry(1.f, 1.f), *aMaterial);
			std::cout << "shape: Capsule" << std::endl;
		}
		_static->attachShape(*aShape);
	}

	PhysicStatic::PhysicStatic(PxPhysics* SDK, PhysicDynamic* physicDynamic)
	{
		type = ETypePhysic::STATIC;

		int nb = physicDynamic->GetRigid()->getNbShapes();

		PxShape* shape;
		physicDynamic->GetRigid()->getShapes(&shape, nb);

		// Prendre les valeurs du dynamic
		_static = SDK->createRigidStatic(PxTransform(physicDynamic->GetRigid()->getGlobalPose()));
		std::cout << "Static ==> position: {" << _static->getGlobalPose().p.x << ", " << _static->getGlobalPose().p.y << ", " << _static->getGlobalPose().p.z << "}" << std::endl;
		std::cout << "nb of shape : " << nb << std::endl;
		for (int i = 0; i < nb; i++)
		{
			std::cout << "attach one shape" << std::endl;
			_static->attachShape(shape[i]);
			physicDynamic->GetRigid()->detachShape(shape[i]);
		}
	}


	PhysicStatic::PhysicStatic(const PhysicStatic& ps) : IPhysicType(ps)
	{
		_static = ps._static;
	}

	PhysicStatic::PhysicStatic(PhysicStatic&& ps) : IPhysicType(ps)
	{
		_static = std::move(ps._static);
	}

	PhysicStatic::~PhysicStatic()
	{
	}

	void PhysicStatic::print()
	{
		std::cout << "Je suis static" << std::endl;
	}

	PxRigidStatic* PhysicStatic::GetRigid() const
	{
		return _static;
	}
}