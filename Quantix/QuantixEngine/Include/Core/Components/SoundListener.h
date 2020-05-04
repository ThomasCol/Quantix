#ifndef __SOUNDLISTENER_H__
#define __SOUNDLISTENER_H__

#include "Core/DLLHeader.h"
#include "Core/DataStructure/Component.h"

namespace Quantix::Core::Components
{
	class QUANTIX_API SoundListener : public Quantix::Core::DataStructure::Component
	{
		private:

			#pragma region Attributes

			QXuint	_listenerID;

			#pragma endregion

		public:

			#pragma region Constructors & Destructor

			/**
			 * @brief Construct a new SoundListener object
			 *
			 */
			SoundListener();

			/**
			 * @brief Construct a new SoundListener object by copy
			 *
			 * @param copy SoundListener
			 */
			SoundListener(const SoundListener& copy) noexcept;

			/**
			 * @brief Construct a new SoundListener object by move
			 *
			 * @param copy SoundListener
			 */
			SoundListener(SoundListener&& copy) noexcept;

			SoundListener(Core::DataStructure::GameComponent* object);

			/**
			 * @brief Destroy the SoundListener object
			 *
			 */
			~SoundListener();

			#pragma endregion

			#pragma region Methods

			SoundListener*	Copy() const override;

			virtual void	Init(Quantix::Core::DataStructure::GameComponent* object) override;

			/**
			 * @brief Update position and rotation attributes of the listener
			 *
			 */
			void			UpdateAttributes();

			#pragma endregion
			CLASS_REGISTRATION(Quantix::Core::DataStructure::Component);
	};
}
#endif //__SOUNDLISTENER_H__