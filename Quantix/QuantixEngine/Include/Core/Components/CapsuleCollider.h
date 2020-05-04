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

		CapsuleCollider() = default;
		CapsuleCollider(DataStructure::GameComponent* par);
		CapsuleCollider(const CapsuleCollider& par) noexcept;
		CapsuleCollider(CapsuleCollider&& other) noexcept;
		~CapsuleCollider() noexcept = default;
#pragma endregion

#pragma region Accessors

		QXfloat GetRadius();
		void SetRadius(QXfloat);

		QXfloat GetHalfHeight();
		void SetHalfHeight(QXfloat);

#pragma endregion

		CapsuleCollider* Copy() const override;
		void Init(DataStructure::GameComponent* par) override;

		void Destroy() override {};


		CLASS_REGISTRATION(Quantix::Core::DataStructure::Component, Quantix::Core::Components::ICollider);
	};
}
#endif

