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


	class QUANTIX_API ICollider : public Core::DataStructure::Component
	{
	protected:
#pragma region Attributes

		QXint _idShape { -1 };
		EPhysXType _type { EPhysXType::DEFAULT };

#pragma endregion

	public:
#pragma region Constructors
		ICollider() = delete;
		explicit ICollider(DataStructure::GameComponent* par) noexcept;
		ICollider(const ICollider& col) noexcept;
		ICollider(ICollider&& col) noexcept;
		virtual ~ICollider() = default;
#pragma endregion

#pragma region Functions

#pragma region Operators

		ICollider& operator=(const ICollider& other) noexcept;
		ICollider& operator=(ICollider&& other) noexcept;

#pragma endregion

#pragma endregion

	};
}

#endif

