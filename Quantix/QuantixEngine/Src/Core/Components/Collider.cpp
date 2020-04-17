#include "Core/Components/Collider.h"
#include "Core/DataStructure/GameComponent.h"

RTTR_PLUGIN_REGISTRATION
{
	using namespace Quantix::Core::Components;
	rttr::registration::class_<Quantix::Core::Components::ICollider>("Collider")
	.enumeration<Quantix::Core::Components::EPhysXType>("EPhysXType")
		(rttr::value("Default", Quantix::Core::Components::EPhysXType::DEFAULT),
		rttr::value("Directional", Quantix::Core::Components::EPhysXType::STATIC),
		rttr::value("Point", Quantix::Core::Components::EPhysXType::DYNAMIC),
		rttr::value("Spot", Quantix::Core::Components::EPhysXType::COUNT))
	.property("idShape", &Quantix::Core::Components::ICollider::idShape)
	.property("type", &Quantix::Core::Components::ICollider::type);
}

namespace Quantix::Core::Components
{
	ICollider::ICollider(DataStructure::GameComponent* par) noexcept:
		Core::DataStructure::Component(par)
	{}

	ICollider::ICollider(const ICollider& col) noexcept :
		Core::DataStructure::Component(col),
		idShape {col.idShape},
		type	{col.type}
	{}

	ICollider::ICollider(ICollider&& col) noexcept :
		Core::DataStructure::Component(col),
		idShape{ std::move(col.idShape) },
		type{ std::move(col.type) }
	{}

	ICollider& ICollider::operator=(const ICollider& other) noexcept
	{
		idShape = other.idShape;
		type = other.type;

		return *this;
	}

	ICollider& ICollider::operator=(ICollider&& other) noexcept
	{
		idShape = std::move(other.idShape);
		type = std::move(other.type);

		return *this;
	}
}