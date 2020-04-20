#include "Core/Components/CubeCollider.h"
#include "Core/DataStructure/GameComponent.h"

RTTR_PLUGIN_REGISTRATION
{
	rttr::registration::class_<Quantix::Core::Components::CubeCollider>("CubeCollider");
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