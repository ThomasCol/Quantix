#ifndef _COLLIDER_H_
#define _COLLIDER_H_

#include "Core/DLLHeader.h"
#include "Core/DataStructure/Component.h"
#include "rttrEnabled.h"

namespace Quantix::Core::DataStructure
{
	class GameComponent;
}

namespace Quantix::Core::Components
{
	enum class EPhysXType
	{
		DEFAULT,
		STATIC,
		DYNAMIC,
		COUNT
	};

	struct QUANTIX_API ICollider : public virtual Core::DataStructure::Component
	{
#pragma region Attributes

		QXint idShape { -1 };
		EPhysXType physicType { EPhysXType::DEFAULT };

#pragma endregion

#pragma region Constructors
		ICollider() = delete;
		ICollider(DataStructure::GameComponent* par);
		ICollider(const ICollider& col) noexcept;
		ICollider(ICollider&& col) noexcept;
		virtual ~ICollider() = default;
#pragma endregion

#pragma region Functions

#pragma region Operators

		ICollider& operator=(const ICollider& other) noexcept;
		ICollider& operator=(ICollider&& other) noexcept;

#pragma endregion

#pragma region Acessors 
		ICollider* Copy() const override;

#pragma endregion

#pragma endregion
		CLASS_REGISTRATION(Core::DataStructure::Component);
	};
}

#endif

