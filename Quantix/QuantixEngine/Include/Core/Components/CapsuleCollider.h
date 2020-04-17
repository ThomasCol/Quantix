#ifndef __CAPSULECOLLIDER_H__
#define __CAPSULECOLLIDER_H__

#include "Core/Components/Collider.h"
#include "Core/DLLHeader.h"
#include "rttrEnabled.h"

namespace Quantix::Core::DataStructure
{
	class GameComponent;
}

namespace Quantix::Core::Components
{
	struct QUANTIX_API CapsuleCollider : public ICollider
	{
#pragma region Constructors

		CapsuleCollider(DataStructure::GameComponent* par) noexcept;
		CapsuleCollider(const CapsuleCollider& par) noexcept;
		CapsuleCollider(CapsuleCollider&& other) noexcept;
		~CapsuleCollider() noexcept = default;

#pragma endregion
		CLASS_REGISTRATION(Quantix::Core::Components::ICollider);
	};
}
#endif

