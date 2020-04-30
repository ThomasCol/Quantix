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

		PlaneCollider() = default;
		PlaneCollider(DataStructure::GameComponent* par);
		PlaneCollider(const PlaneCollider& par) noexcept;
		PlaneCollider(PlaneCollider&& other) noexcept;
		~PlaneCollider() noexcept = default;

#pragma endregion

		PlaneCollider* Copy() const override;
		void Init(DataStructure::GameComponent* par) override;

		CLASS_REGISTRATION(Quantix::Core::DataStructure::Component, Quantix::Core::Components::ICollider);
	};
}
#endif

