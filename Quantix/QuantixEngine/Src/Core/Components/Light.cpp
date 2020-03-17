#include "Core/Components/Light.h"

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
}
