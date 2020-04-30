#include "Core/Components/CubeCollider.h"
#include "Core/DataStructure/GameComponent.h"
#include "Core/Components/Rigidbody.h"
#include "Physic/PhysicHandler.h"

RTTR_PLUGIN_REGISTRATION
{
	rttr::registration::class_<Quantix::Core::Components::CubeCollider>("CubeCollider")
		.constructor<>()
		.constructor<Quantix::Core::DataStructure::GameComponent*>()
		.constructor<const Quantix::Core::Components::CubeCollider&>()
		.constructor<Quantix::Core::Components::CubeCollider&&>()
		.property("HalfExtent", &Quantix::Core::Components::CubeCollider::GetHalfExtents, &Quantix::Core::Components::CubeCollider::SetHalfExtents);
}

namespace Quantix::Core::Components
{
	CubeCollider::CubeCollider(DataStructure::GameComponent* par):
		ICollider(par)
	{
		if (par->GetComponent<Rigidbody>())
			shape = Physic::PhysicHandler::GetInstance()->CreateCubeCollider(par, true);
		else
			shape = Physic::PhysicHandler::GetInstance()->CreateCubeCollider(par, false);
	}

	CubeCollider::CubeCollider(const CubeCollider& other) noexcept :
		ICollider(other)
	{}

	CubeCollider::CubeCollider(CubeCollider&& other) noexcept :
		ICollider(other)
	{}

	Math::QXvec3 CubeCollider::GetHalfExtents()
	{
		physx::PxBoxGeometry box;
		shape->getBoxGeometry(box);
		physx::PxVec3 vec = box.halfExtents;
		return Math::QXvec3(vec.x, vec.y, vec.z);
	}

	void CubeCollider::SetHalfExtents(Math::QXvec3 vec)
	{
		scale = vec * 2;
		shape->setGeometry(physx::PxBoxGeometry(vec.x, vec.y, vec.z));
	}

	CubeCollider* CubeCollider::Copy() const
	{
		return new CubeCollider(*this);
	}

	void CubeCollider::Init(DataStructure::GameComponent* par)
	{
		typeShape = ETypeShape::CUBE;
		_object = par;
		_isDestroyed = false;
		_isEnable = true;

		if (par->GetComponent<Rigidbody>())
		{
			shape = Physic::PhysicHandler::GetInstance()->CreateCubeCollider(par, true);
			actorPhysic = Physic::PhysicHandler::GetInstance()->GetObject(par, true);
		}
		else
		{
			shape = Physic::PhysicHandler::GetInstance()->CreateCubeCollider(par, false);
			actorPhysic = Physic::PhysicHandler::GetInstance()->GetObject(par, false);
		}
	}
}