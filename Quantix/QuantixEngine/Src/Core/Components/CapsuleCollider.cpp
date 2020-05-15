#include "Core/Components/CapsuleCollider.h"
#include "Core/DataStructure/GameComponent.h"
#include "Core/Components/Rigidbody.h"
#include "Physic/PhysicHandler.h"

RTTR_PLUGIN_REGISTRATION
{
	rttr::registration::class_<Quantix::Core::Components::CapsuleCollider>("CapsuleCollider")
	.constructor<>()
	.constructor<Quantix::Core::DataStructure::GameComponent*>()
	.constructor<const Quantix::Core::Components::CapsuleCollider&>()
	.constructor<Quantix::Core::Components::CapsuleCollider&&>()
	.property("Radius", &Quantix::Core::Components::CapsuleCollider::GetRadius, &Quantix::Core::Components::CapsuleCollider::SetRadius)
	.property("HalfHeight", &Quantix::Core::Components::CapsuleCollider::GetHalfHeight, &Quantix::Core::Components::CapsuleCollider::SetHalfHeight);
}

namespace Quantix::Core::Components
{
	CapsuleCollider::CapsuleCollider(DataStructure::GameComponent* par):
		ICollider(par)
	{
		// Create Shape in physic
		if (par->GetComponent<Rigidbody>())
			shape = Physic::PhysicHandler::GetInstance()->CreateCapsuleCollider(par, true);
		else
			shape = Physic::PhysicHandler::GetInstance()->CreateCapsuleCollider(par, false);
	}

	CapsuleCollider::CapsuleCollider(const CapsuleCollider& other) noexcept :
		ICollider(other)
	{}

	CapsuleCollider::CapsuleCollider(CapsuleCollider&& other) noexcept :
		ICollider(other)
	{}

	QXfloat CapsuleCollider::GetRadius()
	{
		physx::PxCapsuleGeometry cap;
		shape->getCapsuleGeometry(cap);
		return cap.radius;
	}

	void CapsuleCollider::SetRadius(QXfloat f)
	{
		scale.x = f;
		scale.z = f;

		shape->setGeometry(physx::PxCapsuleGeometry(physx::PxReal(f), physx::PxReal(GetHalfHeight())));
	}

	QXfloat CapsuleCollider::GetHalfHeight()
	{
		physx::PxCapsuleGeometry cap;
		shape->getCapsuleGeometry(cap);
		return cap.halfHeight;
	}

	void CapsuleCollider::SetHalfHeight(QXfloat f)
	{
		scale.y = 2 * GetRadius() * f;
		shape->setGeometry(physx::PxCapsuleGeometry(physx::PxReal(GetRadius()), physx::PxReal(f)));
	}

	CapsuleCollider* CapsuleCollider::Copy() const
	{
		return new CapsuleCollider(*this);
	}

	void CapsuleCollider::Init(DataStructure::GameComponent* par)
	{
		typeShape = ETypeShape::CAPSULE;
		_object = par;
		_isDestroyed = false;
		_isEnable = true;

		// Create shape and Init Pointer On Actor physic
		if (par->GetComponent<Rigidbody>())
		{
			shape = Physic::PhysicHandler::GetInstance()->CreateCapsuleCollider(par, true);
			actorPhysic = Physic::PhysicHandler::GetInstance()->GetObject(par, true);
		}
		else
		{
			shape = Physic::PhysicHandler::GetInstance()->CreateCapsuleCollider(par, false);
			actorPhysic = Physic::PhysicHandler::GetInstance()->GetObject(par, false);
		}
	}
}