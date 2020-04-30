#ifndef __SPHERECOLLIDER_H__
#define __SPHERECOLLIDER_H__

#include "Core/Components/Collider.h"
#include "Core/DLLHeader.h"
#include "Core/MathHeader.h"
#include "rttrEnabled.h"

namespace Quantix::Core::DataStructure
{
	class GameComponent;
}

namespace Quantix::Core::Components
{
	struct QUANTIX_API SphereCollider : public virtual ICollider
	{
#pragma region Constructors

		SphereCollider() = default;
		SphereCollider(DataStructure::GameComponent* par);
		SphereCollider(const SphereCollider& par) noexcept;
		SphereCollider(SphereCollider&& other) noexcept;
		~SphereCollider() noexcept = default;
		
#pragma endregion

#pragma region Accessors

		QXfloat GetRadius();
		void SetRadius(QXfloat f);

#pragma endregion

		SphereCollider* Copy() const override;
		void Init(DataStructure::GameComponent* par) override;

		CLASS_REGISTRATION(Quantix::Core::DataStructure::Component, Quantix::Core::Components::ICollider);
	};
}
#endif
