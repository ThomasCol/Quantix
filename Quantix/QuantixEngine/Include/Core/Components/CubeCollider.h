#ifndef __CUBECOLLIDER_H__
#define __CUBECOLLIDER_H__

#include "Core/Components/Collider.h"
#include "Core/DLLHeader.h"
#include "rttrEnabled.h"

namespace Quantix::Core::DataStructure
{
	class GameComponent;
}

namespace Quantix::Core::Components
{
	struct QUANTIX_API CubeCollider : public ICollider
	{
#pragma region Constructors

		CubeCollider(DataStructure::GameComponent* par) noexcept;
		CubeCollider(const CubeCollider& par) noexcept;
		CubeCollider(CubeCollider&& other) noexcept;
		~CubeCollider() noexcept = default;

#pragma endregion
		CLASS_REGISTRATION(Quantix::Core::Components::ICollider);
	};
}
#endif

