#ifndef __SPHERECOLLIDER_H__
#define __SPHERECOLLIDER_H__

#include "Core/Components/Collider.h"
#include "Core/DLLHeader.h"
#include "rttrEnabled.h"

namespace Quantix::Core::DataStructure
{
	class GameComponent;
}

namespace Quantix::Core::Components
{
	struct QUANTIX_API SphereCollider : public ICollider
	{
#pragma region Constructors

		SphereCollider(DataStructure::GameComponent* par) noexcept;
		SphereCollider(const SphereCollider& par) noexcept;
		SphereCollider(SphereCollider&& other) noexcept;
		~SphereCollider() noexcept = default;
		
#pragma endregion
		CLASS_REGISTRATION(Quantix::Core::Components::ICollider);
	};
}
#endif
