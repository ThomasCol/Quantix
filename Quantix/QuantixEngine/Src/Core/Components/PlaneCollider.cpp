#include "Core/Components/PlaneCollider.h"
#include "Core/DataStructure/GameComponent.h"
#include "Core/Components/Rigidbody.h"
#include "Physic/PhysicHandler.h"

RTTR_PLUGIN_REGISTRATION
{
	rttr::registration::class_<Quantix::Core::Components::PlaneCollider>("PlaneCollider")
		.constructor<>()
		.constructor<Quantix::Core::DataStructure::GameComponent*>()
		.constructor<const Quantix::Core::Components::PlaneCollider&>()
		.constructor<Quantix::Core::Components::PlaneCollider&&>();
}

namespace Quantix::Core::Components
{
	PlaneCollider::PlaneCollider(DataStructure::GameComponent* par):
		ICollider(par)
	{}

	PlaneCollider::PlaneCollider(const PlaneCollider& other) noexcept :
		ICollider(other)
	{}

	PlaneCollider::PlaneCollider(PlaneCollider&& other) noexcept :
		ICollider(other)
	{}

	PlaneCollider* PlaneCollider::Copy() const
	{
		return new PlaneCollider(*this);
	}

	void PlaneCollider::Init(DataStructure::GameComponent* par)
	{
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