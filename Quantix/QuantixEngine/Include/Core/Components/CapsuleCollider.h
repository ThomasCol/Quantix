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

		/**
		 * @brief Construct a new Capsule Collider object
		 * 
		 */
		CapsuleCollider() = default;

		/**
		 * @brief Construct a new Capsule Collider object
		 * 
		 * @param par parent of the Collider
		 */
		CapsuleCollider(DataStructure::GameComponent* par);

		/**
		 * @brief Construct a new Capsule Collider object
		 * 
		 * @param other CapsuleCollider to Copy 
		 */
		CapsuleCollider(const CapsuleCollider& other) noexcept;

		/**
		 * @brief Construct a new Capsule Collider object
		 * 
		 * @param other CapsuleCollider to move 
		 */
		CapsuleCollider(CapsuleCollider&& other) noexcept;

		/**
		 * @brief Destroy the Capsule Collider object
		 * 
		 */
		~CapsuleCollider() noexcept = default;
#pragma endregion

#pragma region Accessors

		/**
		 * @brief Get the Radius object
		 * 
		 * @return QXfloat Radius of the Capsule
		 */
		QXfloat GetRadius() noexcept;

		/**
		 * @brief Set the Radius object
		 * 
		 * @param rad new radius of the capsule
		 */
		void SetRadius(QXfloat rad) noexcept;

		/**
		 * @brief Get the Half Height object
		 * 
		 * @return QXfloat Height of the Capsule
		 */
		QXfloat GetHalfHeight() noexcept;

		/**
		 * @brief Set the Half Height object
		 * 
		 * @param hei new height of the capsule
		 */
		void SetHalfHeight(QXfloat hei) noexcept;

#pragma endregion

		/**
		 * @brief Copy a CapsuleCollider
		 * 
		 * @return CapsuleCollider* new CapsuleCollider
		 */
		CapsuleCollider* Copy() const override;

		/**
		 * @brief Init new CapsuleCollider
		 * 
		 * @param par Parent of the CapsuleCollider
		 */
		void Init(DataStructure::GameComponent* par) override;

		CLASS_REGISTRATION(Quantix::Core::DataStructure::Component, Quantix::Core::Components::ICollider);
	};
}
#endif

