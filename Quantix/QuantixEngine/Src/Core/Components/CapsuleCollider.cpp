#include "Core/Components/CapsuleCollider.h"
#include "Core/DataStructure/GameComponent.h"

RTTR_PLUGIN_REGISTRATION
{
	rttr::registration::class_<Quantix::Core::Components::CapsuleCollider>("CapsuleCollider");
}

namespace Quantix::Core::Components
{
	CapsuleCollider::CapsuleCollider(DataStructure::GameComponent* par) noexcept :
		ICollider(par)
	{}

	CapsuleCollider::CapsuleCollider(const CapsuleCollider& other) noexcept :
		ICollider(other)
	{}

	CapsuleCollider::CapsuleCollider(CapsuleCollider&& other) noexcept :
		ICollider(other)
	{}
}