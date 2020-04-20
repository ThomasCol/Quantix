#include "Core/Components/CapsuleCollider.h"
#include "Core/DataStructure/GameComponent.h"

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
	{}

	CapsuleCollider::CapsuleCollider(const CapsuleCollider& other) noexcept :
		ICollider(other)
	{}

	CapsuleCollider::CapsuleCollider(CapsuleCollider&& other) noexcept :
		ICollider(other)
	{}

	CapsuleCollider* CapsuleCollider::Copy() const
	{
		return new CapsuleCollider(*this);
	}
}