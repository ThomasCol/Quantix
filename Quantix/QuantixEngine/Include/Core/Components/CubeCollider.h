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
		CubeCollider() = default;
		CubeCollider(DataStructure::GameComponent* par);
		CubeCollider(const CubeCollider& par) noexcept;
		CubeCollider(CubeCollider&& other) noexcept;
		~CubeCollider() noexcept = default;
#pragma endregion

#pragma region Accessors

		Math::QXvec3 GetHalfExtents();
		void SetHalfExtents(Math::QXvec3);

#pragma endregion

		CubeCollider* Copy() const override;

		void Init(DataStructure::GameComponent* par) override;

		CLASS_REGISTRATION(Quantix::Core::DataStructure::Component, Quantix::Core::Components::ICollider);
	};
}
#endif

