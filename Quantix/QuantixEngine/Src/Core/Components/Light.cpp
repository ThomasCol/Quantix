#include "Core/Components/Light.h"
#include "Core/DataStructure/GameComponent.h"

RTTR_PLUGIN_REGISTRATION
{
	rttr::registration::class_<Quantix::Core::Components::Light>("Light")
	.constructor<>()
	.constructor<const Quantix::Core::Components::Light&>()
	.constructor<Quantix::Core::Components::Light&&>()
	.constructor<Quantix::Core::DataStructure::GameComponent*>()
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
	Light::Light() noexcept :
		ambient {0},
		diffuse {0},
		specular {0},
		type {0}
	{}

	Light::Light(const Light& light) noexcept :
		ambient {light.ambient},
		diffuse {light.diffuse},
		specular {light.specular},
		type {light.type}
	{}

	Light::Light(Light&& light) noexcept :
		ambient {std::move(light.ambient)},
		diffuse {std::move(light.diffuse)},
		specular {std::move(light.specular)},
		type {std::move(light.type)}
	{}

	Light::Light(Math::QXvec3 ambientValue, Math::QXvec3 diffuseValue, Math::QXvec3 specularValue, ELightType lightType) noexcept :
		ambient {ambientValue},
		diffuse {diffuseValue},
		specular {specularValue},
		type {lightType}
	{}

	Light::Light(Core::DataStructure::GameComponent* obj) :
		Component(obj)
	{
	}
	Light* Light::Copy() const
	{
		return new Light(*this);
	}
}
