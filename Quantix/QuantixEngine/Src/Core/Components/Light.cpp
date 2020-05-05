#include "Core/Components/Light.h"
#include "Core/DataStructure/GameComponent.h"

RTTR_PLUGIN_REGISTRATION
{
	rttr::registration::class_<Quantix::Core::Components::Light>("Light")
	.constructor<>()
	.constructor<const Quantix::Core::Components::Light&>()
	.constructor<Quantix::Core::Components::Light&&>()
	.enumeration<Quantix::Core::Components::ELightType>("ELightType")
					 (rttr::value("Default", Quantix::Core::Components::ELightType::DEFAULT),
					 rttr::value("Directional", Quantix::Core::Components::ELightType::DIRECTIONAL),
					 rttr::value("Point", Quantix::Core::Components::ELightType::POINT),
					 rttr::value("Spot", Quantix::Core::Components::ELightType::SPOT),
					 rttr::value("Count", Quantix::Core::Components::ELightType::COUNT))
	.property("type", &Quantix::Core::Components::Light::type)
	.property("ambient", &Quantix::Core::Components::Light::ambient)
	.property("diffuse", &Quantix::Core::Components::Light::diffuse)
	.property("specular", &Quantix::Core::Components::Light::specular)
	.property("direction", &Quantix::Core::Components::Light::direction)
	.property("position", &Quantix::Core::Components::Light::position)
	.property("constant", &Quantix::Core::Components::Light::constant)
	.property("linear", &Quantix::Core::Components::Light::linear)
	.property("quadratic", &Quantix::Core::Components::Light::quadratic)
	.property("cutOff", &Quantix::Core::Components::Light::cutOff)
	.property("outerCutOff", &Quantix::Core::Components::Light::outerCutOff);
}

namespace Quantix::Core::Components
{
	Light* Light::Copy() const noexcept
	{
		return new Light(*this);
	}
	void Light::Init(Core::DataStructure::GameComponent* object) noexcept
	{
		_object = object;
		_isDestroyed = false;
		_isEnable = true;
	}
}
