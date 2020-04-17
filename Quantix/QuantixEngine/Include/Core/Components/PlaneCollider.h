#ifndef __PLANECOLLIDER_H__
#define __PLANECOLLIDER_H__

#include "Core/Components/Collider.h"
#include "Core/DLLHeader.h"
#include "rttrEnabled.h"

namespace Quantix::Core::DataStructure
{
	class GameComponent;
}

namespace Quantix::Core::Components
{
	struct QUANTIX_API PlaneCollider : public ICollider
	{
#pragma region Constructors

		PlaneCollider(DataStructure::GameComponent* par) noexcept;
		PlaneCollider(const PlaneCollider& par) noexcept;
		PlaneCollider(PlaneCollider&& other) noexcept;
		~PlaneCollider() noexcept = default;

#pragma endregion
		CLASS_REGISTRATION(Quantix::Core::Components::ICollider);
	};
}
#endif

