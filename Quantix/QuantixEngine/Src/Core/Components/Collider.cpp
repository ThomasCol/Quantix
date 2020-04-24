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
	.enumeration<Quantix::Core::Components::EPhysXType>("EPhysXType")
		(rttr::value("Default", Quantix::Core::Components::EPhysXType::DEFAULT),
		rttr::value("Directional", Quantix::Core::Components::EPhysXType::STATIC),
		rttr::value("Point", Quantix::Core::Components::EPhysXType::DYNAMIC),
		rttr::value("Spot", Quantix::Core::Components::EPhysXType::COUNT))
	.property("physicType", &Quantix::Core::Components::ICollider::physicType)
	.property("LocalPosition", &Quantix::Core::Components::ICollider::GetPosition, &Quantix::Core::Components::ICollider::SetPosition)
	.property("LocalRotation", &Quantix::Core::Components::ICollider::GetRotation, &Quantix::Core::Components::ICollider::SetRotation);
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
	
	/*ICollider::ICollider(const ICollider& col, ETypeShape type) noexcept :
		Core::DataStructure::Component(col),
		shape {col.shape },
		physicType{col.physicType },
		actorPhysic{col.actorPhysic}
	{

	}*/

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

	ICollider* ICollider::Copy() const
	{
		return new ICollider(*this);
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

	void ICollider::Remove()
	{
		shape->getActor()->detachShape(*shape);
	}
}