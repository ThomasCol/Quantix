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
		// Create Shape in physic
		if (par->GetComponent<Rigidbody>())
			shape = Physic::PhysicHandler::GetInstance()->CreateSphereCollider(par, QX_TRUE);
		else
			shape = Physic::PhysicHandler::GetInstance()->CreateSphereCollider(par, QX_FALSE);
	}
	
	SphereCollider::SphereCollider(const SphereCollider& other) noexcept :
		ICollider(other)
	{}

	SphereCollider::SphereCollider(SphereCollider&& other) noexcept :
		ICollider(other)
	{}

	QXfloat SphereCollider::GetRadius() noexcept
	{
		physx::PxSphereGeometry sphere;
		shape->getSphereGeometry(sphere);
		return sphere.radius;
	}

	void SphereCollider::SetRadius(QXfloat f) noexcept
	{
		scale.x = f;
		scale.y = f;
		scale.z = f;

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
		_isDestroyed = QX_FALSE;
		_isEnable = QX_TRUE;

		// Create shape and Init Pointer On Actor physic
		if (par->GetComponent<Rigidbody>())
		{
			shape = Physic::PhysicHandler::GetInstance()->CreateSphereCollider(par, QX_TRUE);
			actorPhysic = Physic::PhysicHandler::GetInstance()->GetObject(par, QX_TRUE);
		}
		else
		{
			shape = Physic::PhysicHandler::GetInstance()->CreateSphereCollider(par, QX_FALSE);
			actorPhysic = Physic::PhysicHandler::GetInstance()->GetObject(par, QX_FALSE);
		}
		SetCollideFilterCrab(QX_TRUE);
		SetCollideFilterMine(QX_TRUE);
		SetCollideFilterPawn(QX_TRUE);
		SetMyFilterGroup(Physic::FilterGroup::eCRAB);
	}
}