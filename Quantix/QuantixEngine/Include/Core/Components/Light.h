#ifndef __LIGHT_H__
#define __LIGHT_H__

#include <Vec3.h>
#include <Vec2.h>

#include "Core/DLLHeader.h"
#include "Core/DataStructure/Component.h"
#include <Type.h>

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

	struct QUANTIX_API Light : public Quantix::Core::DataStructure::Component
	{
#pragma region Attributes
		QXfloat				_pad0[4] {0};
		Math::QXvec3		direction; QXfloat _pad1{0};
		Math::QXvec3		position; QXfloat _pad2{ 0 };

		Math::QXvec3   		ambient; QXfloat _pad3{ 0 };
		Math::QXvec3   		diffuse; QXfloat _pad4{ 0 };
		Math::QXvec3   		specular;

		QXfloat				constant{ 0 }; 
		QXfloat				linear{0}; 
		QXfloat				quadratic{0};

		QXfloat				cutOff{0};
		QXfloat				outerCutOff{0};

		ELightType			type { ELightType::DEFAULT };
#pragma endregion

#pragma region Constructors

		/**
		 * @brief Construct a new Light object
		 */
		Light() = default;
		/**
		 * @brief Construct a new Light object
		 * 
		 * @param light Light to copy
		 */
		Light(const Light& light) = default;

		/**
		 * @brief Construct a new Light object
		 * 
		 * @param light Light to move
		 */
		Light(Light&& light) = default;

		Light(Core::DataStructure::GameComponent* obj);

		/**
		 * @brief Destroy the Light object
		 */
		~Light() = default;

#pragma endregion

		Light*	Copy() const override;

		void	Init(Core::DataStructure::GameComponent* object) override;

		CLASS_REGISTRATION(Core::DataStructure::Component);
	};
}


#endif // __LIGHT_H__
