#include "Core/Components/Collider.h"
#include "Core/DataStructure/GameComponent.h"
#include "Core/Components//Rigidbody.h"

RTTR_PLUGIN_REGISTRATION
{
	using namespace Quantix::Core::Components;
	rttr::registration::class_<Quantix::Core::Components::ICollider>("Collider")
	.constructor<>()
	.constructor<Quantix::Core::DataStructure::GameComponent*>()
	.constructor<const Quantix::Core::Components::ICollider&>()
	.constructor<Quantix::Core::Components::ICollider&&>()
	.enumeration<Quantix::Physic::FilterGroup::Enum>("FilterGroup")
		(rttr::value("Pawn", Quantix::Physic::FilterGroup::Enum::PAWN),
		rttr::value("Crab", Quantix::Physic::FilterGroup::Enum::eCRAB),
		rttr::value("MineHead", Quantix::Physic::FilterGroup::Enum::eMINE_HEAD))
	.property("ToRender", &Quantix::Core::Components::ICollider::toRender)
	.property("Local Position", &Quantix::Core::Components::ICollider::GetPosition, &Quantix::Core::Components::ICollider::SetPosition)
	.property("Local Rotation", &Quantix::Core::Components::ICollider::GetRotation, &Quantix::Core::Components::ICollider::SetRotation)
	.property("MyGroup", &Quantix::Core::Components::ICollider::GetMyFilterGroup, &Quantix::Core::Components::ICollider::SetMyFilterGroup)
	.property("GroupCollidePawn", &Quantix::Core::Components::ICollider::GetCollideFilterPawn, &Quantix::Core::Components::ICollider::SetCollideFilterPawn)
	.property("GroupCollideMine", &Quantix::Core::Components::ICollider::GetCollideFilterMine, &Quantix::Core::Components::ICollider::SetCollideFilterMine)
	.property("GroupCollideCrab", &Quantix::Core::Components::ICollider::GetCollideFilterCrab, &Quantix::Core::Components::ICollider::SetCollideFilterCrab)
	.property("Query Shape", &Quantix::Core::Components::ICollider::GetShapeFlagSceneQuery, &Quantix::Core::Components::ICollider::SetShapeFlagSceneQuery)
	.property("Simulation Shape", &Quantix::Core::Components::ICollider::GetShapeFlagSimulation, &Quantix::Core::Components::ICollider::SetShapeFlagSimulation)
	.property("Trigger Shape", &Quantix::Core::Components::ICollider::GetShapeFlagTrigger, &Quantix::Core::Components::ICollider::SetShapeFlagTrigger)
	.property("Visualization Shape", &Quantix::Core::Components::ICollider::GetShapeFlagVisualization, &Quantix::Core::Components::ICollider::SetShapeFlagVisualization);
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

	void ICollider::SetCollideFilterPawn(bool b)
	{
		collideFilter.pawn = b;

		physx::PxFilterData filterData;
		filterData.word0 = shape->getSimulationFilterData().word0; // word0 = own ID
		
		physx::PxU32 mask;
		if (GetCollideFilterCrab())
			mask |= Physic::FilterGroup::Enum::eCRAB;
		if (GetCollideFilterPawn())
			mask |= Physic::FilterGroup::Enum::PAWN;		
		if (GetCollideFilterMine())
			mask |= Physic::FilterGroup::Enum::eMINE_HEAD;
		filterData.word1 = mask;  // word1 = ID mask to filter pairs that trigger a
								  // contact callback;
		shape->setSimulationFilterData(filterData);
	}

	void ICollider::SetCollideFilterMine(bool b)
	{
		collideFilter.mine = b;

		physx::PxFilterData filterData;
		filterData.word0 = shape->getSimulationFilterData().word0; // word0 = own ID

		physx::PxU32 mask;
		if (GetCollideFilterCrab())
			mask |= Physic::FilterGroup::Enum::eCRAB;
		if (GetCollideFilterPawn())
			mask |= Physic::FilterGroup::Enum::PAWN;
		if (GetCollideFilterMine())
			mask |= Physic::FilterGroup::Enum::eMINE_HEAD;
		filterData.word1 = mask;  // word1 = ID mask to filter pairs that trigger a
								  // contact callback;
		shape->setSimulationFilterData(filterData);
	}

	void ICollider::SetCollideFilterCrab(bool b)
	{
		collideFilter.crab = b;

		physx::PxFilterData filterData;
		filterData.word0 = shape->getSimulationFilterData().word0; // word0 = own ID

		physx::PxU32 mask;
		if (GetCollideFilterCrab())
			mask |= Physic::FilterGroup::Enum::eCRAB;
		if (GetCollideFilterPawn())
			mask |= Physic::FilterGroup::Enum::PAWN;
		if (GetCollideFilterMine())
			mask |= Physic::FilterGroup::Enum::eMINE_HEAD;
		filterData.word1 = mask;  // word1 = ID mask to filter pairs that trigger a
								  // contact callback;
		shape->setSimulationFilterData(filterData);
	}

	void ICollider::SetShapeFlagSceneQuery(bool b)
	{
		shapeFlag.sceneQuery = b;
		shape->setFlag(physx::PxShapeFlag::eSCENE_QUERY_SHAPE, b);
	}

	bool ICollider::GetShapeFlagSceneQuery()
	{
		return shapeFlag.sceneQuery;
	}

	void ICollider::SetShapeFlagSimulation(bool b)
	{
		shapeFlag.simulation = b;
		shape->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, b);
	}

	bool ICollider::GetShapeFlagSimulation()
	{
		return shapeFlag.simulation;
	}

	void ICollider::SetShapeFlagTrigger(bool b)
	{
		shapeFlag.trigger = b;
		shape->setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, b);
	}

	bool ICollider::GetShapeFlagTrigger()
	{
		return shapeFlag.trigger;
	}

	void ICollider::SetShapeFlagVisualization(bool b)
	{
		shapeFlag.visualization = b;
		shape->setFlag(physx::PxShapeFlag::eVISUALIZATION, b);
	}

	bool ICollider::GetShapeFlagVisualization()
	{
		return shapeFlag.visualization;
	}
}