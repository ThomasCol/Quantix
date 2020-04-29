#include "Core/Components/SphereCollider.h"
#include "Core/DataStructure/GameComponent.h"
#include "Core/Components/Rigidbody.h"
#include "Physic/PhysicHandler.h"
#include "Physic/PhysicDynamic.h"
#include "Physic/PhysicStatic.h"

RTTR_PLUGIN_REGISTRATION
{
	rttr::registration::class_<Quantix::Core::Components::SphereCollider>("SphereCollider")
		.constructor<>()
		.constructor<Quantix::Core::DataStructure::GameComponent*>()
		.constructor<const Quantix::Core::Components::SphereCollider&>()
		.constructor<Quantix::Core::Components::SphereCollider&&>()
	.property("Radius", &Quantix::Core::Components::SphereCollider::GetRadius, &Quantix::Core::Components::SphereCollider::SetRadius);
}

namespace Quantix::Core::Components
{
	SphereCollider::SphereCollider(DataStructure::GameComponent* par):
		ICollider(par)
	{
		if (par->GetComponent<Rigidbody>())
			shape = Physic::PhysicHandler::GetInstance()->CreateSphereCollider(par, true);
		else
			shape = Physic::PhysicHandler::GetInstance()->CreateSphereCollider(par, false);
	}

	SphereCollider::SphereCollider(const SphereCollider& other) noexcept :
		ICollider(other)
	{}

	SphereCollider::SphereCollider(SphereCollider&& other) noexcept :
		ICollider(other)
	{}

	QXfloat SphereCollider::GetRadius()
	{
		physx::PxSphereGeometry sphere;
		shape->getSphereGeometry(sphere);
		return sphere.radius;
	}

	void SphereCollider::SetRadius(QXfloat f)
	{
		shape->setGeometry(physx::PxSphereGeometry(f));
	}

	SphereCollider* SphereCollider::Copy() const
	{
		return new SphereCollider(*this);
	}

	void SphereCollider::Init(DataStructure::GameComponent* par)
	{
		typeShape = ETypeShape::SPHERE;
		_object = par;
		_isDestroyed = false;
		_isEnable = true;

		if (par->GetComponent<Rigidbody>())
		{
			shape = Physic::PhysicHandler::GetInstance()->CreateSphereCollider(par, true);
			actorPhysic = Physic::PhysicHandler::GetInstance()->GetObject(par, true);
		}
		else
		{
			shape = Physic::PhysicHandler::GetInstance()->CreateSphereCollider(par, false);
			actorPhysic = Physic::PhysicHandler::GetInstance()->GetObject(par, false);
		}

		
	}
}