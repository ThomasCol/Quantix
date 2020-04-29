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
	.constructor<Quantix::Core::Components::CapsuleCollider&&>();
}

namespace Quantix::Core::Components
{
	CapsuleCollider::CapsuleCollider(DataStructure::GameComponent* par):
		ICollider(par)
	{
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
		shape->setGeometry(physx::PxCapsuleGeometry(physx::PxReal(GetRadius()), physx::PxReal(f)));
	}

	CapsuleCollider* CapsuleCollider::Copy() const
	{
		return new CapsuleCollider(*this);
	}

	void CapsuleCollider::Init(DataStructure::GameComponent* par)
	{
		_object = par;
		_isDestroyed = false;
		_isEnable = true;

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