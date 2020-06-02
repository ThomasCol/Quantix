#include "Core/DataStructure/Component.h"
#include "Core/DataStructure/GameComponent.h"

RTTR_PLUGIN_REGISTRATION
{
	rttr::registration::class_<Quantix::Core::DataStructure::Component>("Component")
	.property("Enable", &Quantix::Core::DataStructure::Component::IsEnable, &Quantix::Core::DataStructure::Component::SetActive)
	.method("Copy", &Quantix::Core::DataStructure::Component::Copy);
}

namespace Quantix::Core::DataStructure
{
	Component::Component()  noexcept :
		_object{ nullptr },
		_isDestroyed{ false },
		_isEnable(true)
	{}

	Component::Component(const Component& comp)  noexcept :
		_object{ comp._object },
		_isDestroyed{ false },
		_isEnable(true)
	{}

	Component::Component(Component&& comp) noexcept :
		_object{ std::move(comp._object) },
		_isDestroyed{ std::move(comp._isDestroyed) },
		_isEnable{ std::move(comp._isEnable) }
	{}

	Component::Component(GameComponent* obj)  noexcept :
		_object{ obj },
		_isDestroyed{ false },
		_isEnable{ true }
	{}

	GameComponent* Component::GetObject() noexcept
	{
		return _object;
	}

	void		Component::EraseEndOfFrame() noexcept
	{
		_isDestroyed = true;
	}

	QXbool		Component::IsDestroyed() const noexcept
	{
		return _isDestroyed;
	}
}
