#include "Core/Components/Collider.h"
#include "Core/DataStructure/GameComponent.h"

namespace Quantix::Core::Components
{
	ICollider::ICollider(DataStructure::GameComponent* par) noexcept:
		Core::DataStructure::Component(par)
	{}

	ICollider::ICollider(const ICollider& col) noexcept :
		Core::DataStructure::Component(col),
		_idShape {col._idShape},
		_type	{col._type}
	{}

	ICollider::ICollider(ICollider&& col) noexcept :
		Core::DataStructure::Component(col),
		_idShape{ std::move(col._idShape) },
		_type{ std::move(col._type) }
	{}

	ICollider& ICollider::operator=(const ICollider& other) noexcept
	{
		_idShape = other._idShape;
		_type = other._type;

		return *this;
	}

	ICollider& ICollider::operator=(ICollider&& other) noexcept
	{
		_idShape = std::move(other._idShape);
		_type = std::move(other._type);

		return *this;
	}
}