#include "Core/Components/SphereCollider.h"
#include "Core/DataStructure/GameComponent.h"

RTTR_PLUGIN_REGISTRATION
{
	rttr::registration::class_<Quantix::Core::Components::SphereCollider>("SphereCollider");
}

namespace Quantix::Core::Components
{
	SphereCollider::SphereCollider(DataStructure::GameComponent* par) noexcept :
		ICollider(par)
	{}

	SphereCollider::SphereCollider(const SphereCollider& other) noexcept :
		ICollider(other)
	{}

	SphereCollider::SphereCollider(SphereCollider&& other) noexcept :
		ICollider(other)
	{}
}