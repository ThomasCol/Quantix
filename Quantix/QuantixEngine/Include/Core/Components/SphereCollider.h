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

		/**
		 * @brief Construct a new Sphere Collider object
		 * 
		 */
		SphereCollider() = default;

		/**
		 * @brief Construct a new Sphere Collider object
		 * 
		 * @param par Parent of the New SphereCollider
		 */
		SphereCollider(DataStructure::GameComponent* par);

		/**
		 * @brief Construct a new Sphere Collider object
		 * 
		 * @param par SphereCollider to copy
		 */
		SphereCollider(const SphereCollider& par) noexcept;

		/**
		 * @brief Construct a new Sphere Collider object
		 * 
		 * @param other SphereCollider to Move
		 */
		SphereCollider(SphereCollider&& other) noexcept;

		/**
		 * @brief Destroy the Sphere Collider object
		 * 
		 */
		~SphereCollider() noexcept = default;
		
#pragma endregion

#pragma region Accessors

		/**
		 * @brief Get the Radius object
		 * 
		 * @return QXfloat Value of Radius
		 */
		QXfloat GetRadius();

		/**
		 * @brief Set the Radius object
		 * 
		 * @param f New Value of the Radius
		 */
		void SetRadius(QXfloat f);

#pragma endregion

		/**
		 * @brief Copy New Collider
		 * 
		 * @return SphereCollider* Return the New Collider
		 */
		SphereCollider* Copy() const override;

		/**
		 * @brief Init a Collider
		 * 
		 * @param par Parent of the SphereCollider
		 */
		void Init(DataStructure::GameComponent* par) override;

		CLASS_REGISTRATION(Quantix::Core::DataStructure::Component, Quantix::Core::Components::ICollider);
	};
}
#endif
