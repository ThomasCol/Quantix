#ifndef __RIGIDBODY_H__
#define __RIGIDBODY_H__

#include "Core/DLLHeader.h"
#include "Core/DataStructure/Component.h"
#include "rttrEnabled.h"

#include "Physic/IPhysicType.h"
#include "Core/MathHeader.h"

namespace Quantix::Core::DataStructure
{
	class GameComponent;
}

namespace Quantix::Core::Components
{
	struct QUANTIX_API Rigidbody : public Core::DataStructure::Component
	{
#pragma region Attributes
		Physic::IPhysicType* actorPhysic{ nullptr };

		//PhysicHandler* handler {nullptr};
#pragma endregion

#pragma region Constructors

		Rigidbody() = delete;
		Rigidbody(DataStructure::GameComponent* par/*, PhysicHandler* handler*/) noexcept;
		Rigidbody(const Rigidbody& src) noexcept;
		Rigidbody(Rigidbody&& src) noexcept;
		~Rigidbody() noexcept = default;

#pragma endregion

#pragma region Functions

		void AddForce(Math::QXvec3 vec) noexcept;

#pragma endregion
		CLASS_REGISTRATION(Core::DataStructure::Component);
	};
}

#endif

