#include "Core/Components/PlaneCollider.h"
#include "Core/DataStructure/GameComponent.h"

RTTR_PLUGIN_REGISTRATION
{
	rttr::registration::class_<Quantix::Core::Components::PlaneCollider>("PlaneCollider");
}

namespace Quantix::Core::Components
{
	PlaneCollider::PlaneCollider(DataStructure::GameComponent* par) noexcept :
		ICollider(par)
	{}

	PlaneCollider::PlaneCollider(const PlaneCollider& other) noexcept :
		ICollider(other)
	{}

	PlaneCollider::PlaneCollider(PlaneCollider&& other) noexcept :
		ICollider(other)
	{}
}