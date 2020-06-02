#ifndef __BUMPER_H__
#define __BUMPER_H__

#include "Core\Components\Behaviour.h"
#include "Core\DataStructure\GameObject3D.h"
#include "Core\Components\Rigidbody.h"

#include "rttrEnabled.h"

namespace Quantix::Core::Components::Behaviours
{
	class QUANTIX_API Bumper : public Quantix::Core::Components::Behaviour
	{
		private :
			
			#pragma region Attributes

			Math::QXvec3	_force	{ 0.f, 3.f, 0.f };

			#pragma endregion

		public :


			#pragma region Constructors & Destructor

			/**
			 * @brief Construct a new Bumper object
			 *
			 */
			Bumper() = default;

			/**
			 * @brief Construct a new Bumper object
			 *
			 * @param par GameComponent who has this component
			 */
			Bumper(Quantix::Core::DataStructure::GameComponent * par);

			/**
			 * @brief Construct a new Bumper object per copy
			 *
			 */
			Bumper(const Bumper&) = default;

			/**
			 * @brief Construct a new Bumper object per move
			 *
			 */
			Bumper(Bumper&&) = default;

			/**
			 * @brief Destroy the Arms object
			 *
			 */
			~Bumper() = default;

			#pragma endregion

			/**
			 * @brief Create a new Bumper object
			 *
			 * @return Bumper* new Bumper
			 */
			Bumper* Copy() const override;

			#pragma region Methods

			/**
			 * @brief Called when Physic raise an OnTriggerEvent for this behaviour
			 *
			 * @param me
			 * @param other
			 */
			void						OnTrigger(Core::DataStructure::GameObject3D* me, Core::DataStructure::GameObject3D* other) override;

			#pragma region Accessors

			inline const Math::QXvec3&	GetForce() noexcept								{ return _force; };
			inline void					SetForce(const Math::QXvec3& newForce) noexcept { _force = newForce; };
			#pragma endregion

			#pragma endregion

		CLASS_REGISTRATION(Quantix::Core::DataStructure::Component, Quantix::Core::Components::Behaviour);
	};
}

#endif

