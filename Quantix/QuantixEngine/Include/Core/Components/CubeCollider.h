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
	struct QUANTIX_API CubeCollider : public virtual ICollider
	{
#pragma region Constructors

		/**
		 * @brief Construct a new Cube Collider object
		 * 
		 */
		CubeCollider() = default;

		/**
		 * @brief Construct a new Cube Collider object
		 * 
		 * @param par Parent of the CubeCollider
		 */
		CubeCollider(DataStructure::GameComponent* par);

		/**
		 * @brief Construct a new Cube Collider object
		 * 
		 * @param par CubeCollider to copy
		 */
		CubeCollider(const CubeCollider& par) noexcept;

		/**
		 * @brief Construct a new Cube Collider object
		 * 
		 * @param other CubeCollider to move
		 */
		CubeCollider(CubeCollider&& other) noexcept;

		/**
		 * @brief Destroy the Cube Collider object
		 * 
		 */
		~CubeCollider() noexcept = default;
#pragma endregion

#pragma region Accessors

		/**
		 * @brief Get the Half Extents object
		 * 
		 * @return Math::QXvec3 halfExtents Value
		 */
		Math::QXvec3 GetHalfExtents();

		/**
		 * @brief Set the Half Extents object
		 * 
		 * @param extent new HalfExtents
		 */
		void SetHalfExtents(Math::QXvec3 extent);

#pragma endregion

		/**
		 * @brief Copy a CubeCollider
		 * 
		 * @return CubeCollider* New Collider
		 */
		CubeCollider* Copy() const override;

		/**
		 * @brief Init a Collider
		 * 
		 * @param par Parent of the CubeCollider
		 */
		void Init(DataStructure::GameComponent* par) override;

		CLASS_REGISTRATION(Quantix::Core::DataStructure::Component, Quantix::Core::Components::ICollider);
	};
}
#endif

