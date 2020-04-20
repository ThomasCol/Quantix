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
	.property("physicType", &Quantix::Core::Components::ICollider::physicType);
}

namespace Quantix::Core::Components
{
	ICollider::ICollider(DataStructure::GameComponent* par):
		Core::DataStructure::Component(par)
	{}
	
	ICollider::ICollider(const ICollider& col) noexcept :
		Core::DataStructure::Component(col),
		idShape {col.idShape},
		physicType{col.physicType }
	{}

	ICollider::ICollider(ICollider&& col) noexcept :
		Core::DataStructure::Component(col),
		idShape{ std::move(col.idShape) },
		physicType{ std::move(col.physicType) }
	{}

	ICollider& ICollider::operator=(const ICollider& other) noexcept
	{
		idShape = other.idShape;
		physicType = other.physicType;

		return *this;
	}

	ICollider& ICollider::operator=(ICollider&& other) noexcept
	{
		idShape = std::move(other.idShape);
		physicType = std::move(other.physicType);

		return *this;
	}

	ICollider* ICollider::Copy() const
	{
		return new ICollider(*this);
	}
}