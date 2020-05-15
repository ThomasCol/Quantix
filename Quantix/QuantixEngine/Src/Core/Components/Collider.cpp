#include "Core/Components/Collider.h"
#include "Core/DataStructure/GameComponent.h"
#include "Core/Components//Rigidbody.h"

RTTR_PLUGIN_REGISTRATION
{
	using namespace Quantix::Core::Components;
rttr::registration::class_<ICollider>("Collider")
.constructor<>()
.constructor<Quantix::Core::DataStructure::GameComponent*>()
.constructor<const ICollider&>()
.constructor<ICollider&&>()
.enumeration<Quantix::Physic::FilterGroup::Enum>("FilterGroup")
(rttr::value("Pawn", Quantix::Physic::FilterGroup::Enum::PAWN),
	rttr::value("Crab", Quantix::Physic::FilterGroup::Enum::eCRAB),
	rttr::value("MineHead", Quantix::Physic::FilterGroup::Enum::eMINE_HEAD))
	.property("ToRender", &ICollider::toRender)
	.property("Local Position", &ICollider::GetPosition, &ICollider::SetPosition)
	.property("Local Rotation", &ICollider::GetRotation, &ICollider::SetRotation)
	.property("MyGroup", &ICollider::GetMyFilterGroup, &ICollider::SetMyFilterGroup)
	.property("Collide Group", &ICollider::collideFilter)
	.property("Shape Flag", &ICollider::shapeFlag)

	.property("PawnGroup", &ICollider::GetCollideFilterPawn, &ICollider::SetCollideFilterPawn)
	(rttr::metadata("Description", "Collide Group"))
	.property("MineGroup", &ICollider::GetCollideFilterMine, &ICollider::SetCollideFilterMine)
	.property("CrabGroup", &ICollider::GetCollideFilterCrab, &ICollider::SetCollideFilterCrab)
		(rttr::metadata("Description", "End"))

	.property("Query Shape", &ICollider::GetShapeFlagSceneQuery, &ICollider::SetShapeFlagSceneQuery)
		(rttr::metadata("Description", "Shape Flags"))
	.property("Simulation Shape", &ICollider::GetShapeFlagSimulation, &ICollider::SetShapeFlagSimulation)
	.property("Trigger Shape", &ICollider::GetShapeFlagTrigger, &ICollider::SetShapeFlagTrigger)
	.property("Visualization Shape", &ICollider::GetShapeFlagVisualization, &ICollider::SetShapeFlagVisualization)
		(rttr::metadata("Description", "End"));
}

namespace Quantix::Core::Components
{
	ICollider::ICollider(DataStructure::GameComponent* par):
		Core::DataStructure::Component(par)
	{
		if (par->GetComponent<Rigidbody>())
			actorPhysic = Physic::PhysicHandler::GetInstance()->GetObject(par, true);
		else
			actorPhysic = Physic::PhysicHandler::GetInstance()->GetObject(par, false);
	}

	ICollider::ICollider(const ICollider& col) noexcept :
		Core::DataStructure::Component(col),
		shape{ col.shape },
		physicType{ col.physicType },
		actorPhysic{ col.actorPhysic }
	{}

	ICollider::ICollider(ICollider&& col) noexcept :
		Core::DataStructure::Component(col),
		shape{ std::move(col.shape) },
		physicType{ std::move(col.physicType) },
		actorPhysic{ std::move(col.actorPhysic) }
	{}

	ICollider& ICollider::operator=(const ICollider& other) noexcept
	{
		shape = other.shape;
		physicType = other.physicType;
		actorPhysic = other.actorPhysic;

		return *this;
	}

	ICollider& ICollider::operator=(ICollider&& other) noexcept
	{
		shape = std::move(other.shape);
		physicType = std::move(other.physicType);
		actorPhysic = std::move(other.actorPhysic);

		return *this;
	}

	void ICollider::Init(DataStructure::GameComponent* par)
	{
		_object = par;
		_isDestroyed = false;
		_isEnable = true;
		
		if (par->GetComponent<Rigidbody>())
			actorPhysic = Physic::PhysicHandler::GetInstance()->GetObject(par, true);
		else
			actorPhysic = Physic::PhysicHandler::GetInstance()->GetObject(par, false);
	}

	ICollider* ICollider::Copy() const
	{
		return new ICollider(*this);
	}

	void ICollider::UpdateActorPhysic()
	{
		if (_object->GetComponent<Rigidbody>())
			actorPhysic = Physic::PhysicHandler::GetInstance()->GetObject(_object, true);
		else
			actorPhysic = Physic::PhysicHandler::GetInstance()->GetObject(_object, false);
	}

	void ICollider::Destroy()
	{
		shape->getActor()->detachShape(*shape);
	}

	Math::QXvec3 ICollider::GetPosition()
	{
		physx::PxVec3 tmp = shape->getLocalPose().p;
		return Math::QXvec3(tmp.x, tmp.y, tmp.z);
	}

	void ICollider::SetPosition(Math::QXvec3 v)
	{
		physx::PxVec3 tmp = physx::PxVec3(v.x, v.y, v.z);
		shape->setLocalPose(physx::PxTransform(tmp, shape->getLocalPose().q));
	}

	Math::QXquaternion ICollider::GetRotation()
	{
		physx::PxQuat tmp = shape->getLocalPose().q;
		return Math::QXquaternion(tmp.w, tmp.x, tmp.y, tmp.z);
	}

	void ICollider::SetRotation(Math::QXquaternion q)
	{
		physx::PxQuat tmp = physx::PxQuat(q.v.x, q.v.y, q.v.z, q.w);
		shape->setLocalPose(physx::PxTransform(shape->getLocalPose().p, tmp));
	}

	void ICollider::SetMyFilterGroup(Physic::FilterGroup::Enum newGroup)
	{
		physx::PxFilterData filterData;
		filterData.word0 = newGroup; // word0 = own ID
		filterData.word1 = shape->getSimulationFilterData().word1;  // word1 = ID mask to filter pairs that trigger a
										// contact callback;
		shape->setSimulationFilterData(filterData);
	}

	Physic::FilterGroup::Enum ICollider::GetMyFilterGroup()
	{
		return (Physic::FilterGroup::Enum)shape->getSimulationFilterData().word0;
	}
}