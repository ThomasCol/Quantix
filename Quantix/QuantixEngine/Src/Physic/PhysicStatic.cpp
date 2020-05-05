#include "Physic/PhysicStatic.h"
#include "Physic/PhysicDynamic.h"

RTTR_PLUGIN_REGISTRATION
{
	rttr::registration::class_<Quantix::Physic::PhysicStatic>("PhysicDynamic")
	.constructor<>()
	.constructor<physx::PxPhysics*>()
	.constructor<physx::PxPhysics*, Quantix::Physic::PhysicDynamic*>()
	.constructor<const Quantix::Physic::PhysicStatic&>()
	.constructor<Quantix::Physic::PhysicStatic&&>()
	.enumeration<Quantix::Physic::EPhysXShape>("EPhysXShape")
					 (rttr::value("Cube", Quantix::Physic::EPhysXShape::CUBE),
					 rttr::value("Sphere", Quantix::Physic::EPhysXShape::SPHERE),
					 rttr::value("Capsule", Quantix::Physic::EPhysXShape::CAPSULE))
	.property("static", &Quantix::Physic::PhysicStatic::GetRigid, &Quantix::Physic::PhysicStatic::SetRigid);
}

namespace Quantix::Physic
{
	PhysicStatic::PhysicStatic()  noexcept : IPhysicType(ETypePhysic::STATIC)
	{
	}

	PhysicStatic::PhysicStatic(PxPhysics* SDK)  noexcept : IPhysicType(ETypePhysic::STATIC)
	{
		// Create Actor Physic Static
		_static = SDK->createRigidStatic(PxTransform(PxVec3(0, -2, 0)));
	}

	PhysicStatic::PhysicStatic(PxPhysics* SDK, PhysicDynamic* physicDynamic) noexcept
	{
		// Set Type
		type = ETypePhysic::STATIC;

		// Get All Shapes of physicStatic
		int numShapes = physicDynamic->GetRigid()->getNbShapes();
		PxShape** shapes = (PxShape**)malloc(sizeof(PxShape*) * numShapes);
		physicDynamic->GetRigid()->getShapes(shapes, numShapes);

		// Prendre les valeurs du dynamic
		_static = SDK->createRigidStatic(PxTransform(physicDynamic->GetRigid()->getGlobalPose()));

		// Attach shape On the new actor and detach of the old actor
		physx::PxShape* currentShape = nullptr;
		for (int i = 0; i < numShapes; i++)
		{
			currentShape = shapes[i]; 
			physicDynamic->GetRigid()->detachShape(*currentShape);
			_static->attachShape(*currentShape);
		}

		free(shapes);
		
		// Set the userdata
		Core::DataStructure::GameObject3D* data = (Core::DataStructure::GameObject3D*)physicDynamic->GetRigid()->userData;
		_static->userData = data;
	}


	PhysicStatic::PhysicStatic(const PhysicStatic& ps)  noexcept : IPhysicType(ps)
	{
		_static = ps._static;
	}

	PhysicStatic::PhysicStatic(PhysicStatic&& ps) noexcept : IPhysicType(ps)
	{
		_static = std::move(ps._static);
	}

	PhysicStatic::~PhysicStatic() noexcept
	{
	}

	PxRigidStatic* PhysicStatic::GetRigid() noexcept
	{
		return _static;
	}

	void PhysicStatic::SetRigid(PxRigidStatic* st) noexcept
	{
		_static = st;
	}
}