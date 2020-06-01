#ifndef __CHARACTERCONTROLLER_H__
#define __CHARACTERCONTROLLER_H__

#include <Type.h>
#include "Core/DLLHeader.h"
#include "Core/DataStructure/Component.h"

#include "Physic/PhysicHandler.h"

#define GRAVITY Math::QXvec3(0.f, -5.f, 0.f)

namespace Quantix::Core::Components
{
	struct QUANTIX_API CharacterController : public Quantix::Core::DataStructure::Component
	{
		physx::PxCapsuleController* controller {nullptr};

		Math::QXvec3 _velocity;

		/**
		 * @brief Construct a new Character Controller object
		 */
		CharacterController() = default;

		/**
		 * @brief Construct a new Character Controller object
		 * 
		 * @param src CharacterController to copy
		 */
		CharacterController(const CharacterController& src) = default;

		/**
		 * @brief Construct a new Character Controller object
		 * 
		 * @param src CharacterController to move
		 */
		CharacterController(CharacterController&& src) = default;

		/**
		 * @brief Destroy the Character Controller object
		 * 
		 */
		~CharacterController() = default;

		/**
		 * @brief Create a new CharacterController
		 * 
		 * @return CharacterController* new characterController
		 */
		CharacterController* Copy() const noexcept override;

		/**
		 * @brief Init a new CharacterController
		 * 
		 * @param object GameComponent who have this component
		 */
		void	Init(Core::DataStructure::GameComponent* object) noexcept override;

		/**
		 * @brief Destroy Function
		 * 
		 */
		void	Destroy() noexcept override;

		/**
		 * @brief Move the character controller to the position
		 * 
		 * @param vec Position to travel in goal
		 * @param minDist Minimum distance to travel
		 * @param deltaTime Time during the frame
		 */
		void Move(Math::QXvec3 vec, QXint minDist, QXfloat deltaTime);

		void Jump(Math::QXvec3 vec, QXint minDist, QXfloat deltaTime);

		/**
		 * @brief Check if the controller is falling 
		 * 
		 * @return QXbool return true if the controller is falling
		 */
		QXbool CheckIsFalling();

		/**
		 * @brief Get the Radius object
		 * 
		 * @return QXfloat 
		 */
		QXfloat GetRadius();

		/**
		 * @brief Set the Radius object
		 * 
		 * @param f 
		 */
		void SetRadius(QXfloat f);

		/**
		 * @brief Get the Height object
		 * 
		 * @return QXfloat 
		 */
		QXfloat GetHeight();

		/**
		 * @brief Set the Height object
		 * 
		 * @param f 
		 */
		void SetHeight(QXfloat f);

		/**
		 * @brief Change the size of the character controller with foot position always on the grown
		 * 
		 * @param f 
		 */
		void Resize(QXfloat f);

		/**
		 * @brief Get the Up Direction object
		 * 
		 * @return Math::QXvec3 
		 */
		Math::QXvec3 GetUpDirection();

		/**
		 * @brief Set the Up Direction object
		 * 
		 * @param vec 
		 */
		void SetUpDirection(Math::QXvec3 vec);

		/**
		 * @brief Get the Position object
		 * 
		 * @return Math::QXvec3 
		 */
		Math::QXvec3 GetPosition();

		/**
		 * @brief Set the Position object
		 * 
		 * @param v 
		 */
		void SetPosition(Math::QXvec3 v);

		/**
		 * @brief Get the Foot Position object
		 * 
		 * @return Math::QXvec3 
		 */
		Math::QXvec3 GetFootPosition();

		/**
		 * @brief Set the Foot Position object
		 * 
		 * @param v 
		 */
		void SetFootPosition(Math::QXvec3 v);

		/**
		 * @brief Set the Non Walkable Mode object
		 * 
		 * @param mode 
		 */
		void SetNonWalkableMode(Physic::NonWalkableMode mode);

		/**
		 * @brief Get the Non Walkable Mode object
		 * 
		 * @return Physic::NonWalkableMode 
		 */
		Physic::NonWalkableMode GetNonWalkableMode();

		/**
		 * @brief Set the Climbing Mode object
		 * 
		 * @param mode 
		 */
		void SetClimbingMode(Physic::ClimbingMode mode);

		/**
		 * @brief Get the Climbing Mode object
		 * 
		 * @return Physic::ClimbingMode 
		 */
		Physic::ClimbingMode GetClimbingMode();

		/**
		 * @brief Get the Linear Velocity object
		 * 
		 * @return Math::QXvec3 
		 */
		Math::QXvec3 GetLinearVelocity();

		CLASS_REGISTRATION(Core::DataStructure::Component);
	};
}

#endif

