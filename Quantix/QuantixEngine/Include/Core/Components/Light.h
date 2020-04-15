#ifndef __LIGHT_H__
#define __LIGHT_H__

#include <Vec3.h>

#include "Core/DLLHeader.h"
#include "Core/DataStructure/Component.h"
#include "Core/Type.h"

namespace Quantix::Core::Components
{
	enum class ELightType
	{
		DEFAULT,
		DIRECTIONAL,
		POINT,
		SPOT,
		COUNT
	};

	struct QUANTIX_API Light : public virtual Quantix::Core::DataStructure::Component
	{
#pragma region Attributes

		ELightType			type;

		Math::QXvec3   		ambient;
        Math::QXvec3   		diffuse;
        Math::QXvec3   		specular;

		Math::QXvec3		direction;
		Math::QXvec3		position;

		QXfloat				constant{0};
		QXfloat				linear{0};
		QXfloat				quadratic{0};

		QXfloat				cutOff{0};
		QXfloat				outerCutOff{0};

#pragma endregion

#pragma region Constructors

		/**
		 * @brief Construct a new Light object
		 */
		Light() noexcept;

		/**
		 * @brief Construct a new Light object
		 * 
		 * @param light Light to copy
		 */
		Light(const Light& light) noexcept;

		/**
		 * @brief Construct a new Light object
		 * 
		 * @param light Light to move
		 */
		Light(Light&& light) noexcept;

		/**
		 * @brief Construct a new Light object
		 * 
		 * @param ambientValue Vec3 for ambient value
		 * @param diffuseValue Vec3 for diffuse value
		 * @param specularValue Vec3 for specular value
		 * @param lightType Light type value
		 */
		Light(Math::QXvec3 ambientValue, Math::QXvec3 diffuseValue, Math::QXvec3 specularValue, ELightType lightType) noexcept;


		Light(Core::DataStructure::GameComponent* obj);

		/**
		 * @brief Destroy the Light object
		 */
		~Light() = default;

#pragma endregion
		CLASS_REGISTRATION(Core::DataStructure::Component);
	};
}


#endif // __LIGHT_H__
