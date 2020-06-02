#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include <typeinfo>
#include <rttrEnabled.h>
#include "Type.h"
#include "Core/DLLHeader.h"

namespace Quantix::Core::DataStructure
{
	class GameComponent;

	/**
	 * @brief Component Class
	 * 
	 */
	class QUANTIX_API Component
	{
	protected:
		#pragma region Attributes

		GameComponent*	_object;
		QXbool			_isDestroyed;
		QXbool			_isEnable;
		
		#pragma endregion Attributes

	public:
		#pragma region Constructors/Destructor
		/**
		 * @brief Construct a new Component object
		 * 
		 */
		Component() noexcept;

		/**
		 * @brief Construct a new Component object by copy
		 *
		 * @param comp Component
		 */
		Component(const Component& comp) noexcept;

		/**
		 * @brief Construct a new Component object by move
		 *
		 * @param comp Component
		 */
		Component(Component&& comp) noexcept;

		/**
		 * @brief Construct a new Component object
		 *
		 * @param obj GameObject
		 */
		Component(GameComponent* obj) noexcept;

		/**
		 * @brief Destroy the Component object
		 *
		 */
		virtual ~Component() = default;
#pragma endregion Constructors/Destructor

#pragma region Methods
		/**
		 * @brief virtual method that copy the component
		 *
		 * @return Component*
		 */
		virtual Component*					Copy() const = 0;

		/**
		 * @brief virtual method that Init Component
		 *
		 * @param object
		 */
		virtual void						Init(GameComponent * object) = 0;

		/**
		 * @brief
		 *
		 */
		void								EraseEndOfFrame() noexcept;
#pragma region Accessors

		/**
		 * @brief Get the Object object
		 *
		 * @return GameObject*
		 */
		GameComponent*						GetObject() noexcept;

		/**
		 * @brief Get if the Object is Alive
		 *
		 * @return true
		 * @return false
		 */
		QXbool								IsDestroyed() const noexcept;

		/**
		 * @brief Get if the Object is Enable
		 *
		 * @return true
		 * @return false
		 */
		inline virtual QXbool				IsEnable() { return _isEnable; };

		/**
		 * @brief Set the Active object
		 *
		 * @param enable Value to set _isEnable
		 */
		inline virtual void					SetActive(bool enable) { _isEnable = enable; };
#pragma endregion Accessors

#pragma region Inline
		/**
		 * @brief virtual Method for Destroy the Component
		 *
		 */
		inline virtual void					Destroy() {};
		#pragma endregion Inline
		#pragma endregion Methods

		CLASS_REGISTRATION();
	};
}

#endif // !_COMPONENT_H_
