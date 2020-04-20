#include "Core/Components/CubeCollider.h"
#include "Core/DataStructure/GameComponent.h"

RTTR_PLUGIN_REGISTRATION
{
	rttr::registration::class_<Quantix::Core::Components::CubeCollider>("CubeCollider")
		.constructor<>()
		.constructor<Quantix::Core::DataStructure::GameComponent*>()
		.constructor<const Quantix::Core::Components::CubeCollider&>()
		.constructor<Quantix::Core::Components::CubeCollider&&>();
}

namespace Quantix::Core::Components
{
	CubeCollider::CubeCollider(DataStructure::GameComponent* par):
		ICollider(par)
	{}

	CubeCollider::CubeCollider(const CubeCollider& other) noexcept :
		ICollider(other)
	{}

	CubeCollider::CubeCollider(CubeCollider&& other) noexcept :
		ICollider(other)
	{}

	CubeCollider* CubeCollider::Copy() const
	{
		return new CubeCollider(*this);
	}
}