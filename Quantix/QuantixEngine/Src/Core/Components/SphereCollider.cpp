#include "Core/Components/SphereCollider.h"
#include "Core/DataStructure/GameComponent.h"

RTTR_PLUGIN_REGISTRATION
{
	rttr::registration::class_<Quantix::Core::Components::SphereCollider>("SphereCollider")
		.constructor<>()
		.constructor<Quantix::Core::DataStructure::GameComponent*>()
		.constructor<const Quantix::Core::Components::SphereCollider&>()
		.constructor<Quantix::Core::Components::SphereCollider&&>();
}

namespace Quantix::Core::Components
{
	SphereCollider::SphereCollider(DataStructure::GameComponent* par):
		ICollider(par)
	{}

	SphereCollider::SphereCollider(const SphereCollider& other) noexcept :
		ICollider(other)
	{}

	SphereCollider::SphereCollider(SphereCollider&& other) noexcept :
		ICollider(other)
	{}

	SphereCollider* SphereCollider::Copy() const
	{
		return new SphereCollider(*this);
	}
}