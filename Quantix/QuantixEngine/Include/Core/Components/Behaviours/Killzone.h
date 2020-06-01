#ifndef __KILLZONE_H__
#define __KILLZONE_H__

#include "Core\Components\Behaviour.h"
#include "rttrEnabled.h"

namespace Quantix::Gameplay
{
	class QUANTIX_API Killzone : public Quantix::Core::Components::Behaviour
	{
		public:

			/**
			 * @brief Construct a new Killzone object
			 * 
			 */
			Killzone() = default;

			/**
			 * @brief Construct a new Killzone object
			 * 
			 * @param par GameComponent who has this component
			 */
			Killzone(Quantix::Core::DataStructure::GameComponent * par);

			/**
			 * @brief Construct a new Killzone object per copy
			 * 
			 */
			Killzone(const Killzone&) = default;

			/**
			 * @brief Construct a new Killzone object per move
			 * 
			 */
			Killzone(Killzone&&) = default;

			/**
			 * @brief Destroy the Killzone object
			 * 
			 */
			~Killzone() = default;

			/**
			 * @brief Create a new KillZone
			 * 
			 * @return Killzone* new killzone
			 */
			Killzone* Copy() const override;

			/**
			 * @brief Called when Physic raise an OnTriggerEvent for this behaviour
			 * 
			 * @param me 
			 * @param other 
			 */
			void    OnTrigger(Core::DataStructure::GameObject3D* me, Core::DataStructure::GameObject3D* other) override;

			/**
			 * @brief Called when Physic raise an OnContactEvent for this behaviour
			 * 
			 * @param me 
			 * @param other 
			 * @param position Position of the contact
			 * @param normal Normal of the contact
			 */
			void    OnCollision(Core::DataStructure::GameObject3D* me, Core::DataStructure::GameObject3D* other, Math::QXvec3& position, Math::QXvec3& normal) override;

		CLASS_REGISTRATION(Quantix::Core::DataStructure::Component, Quantix::Core::Components::Behaviour);
	};
}
#endif

