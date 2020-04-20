#include "Core/Components/PlaneCollider.h"
#include "Core/DataStructure/GameComponent.h"

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
}