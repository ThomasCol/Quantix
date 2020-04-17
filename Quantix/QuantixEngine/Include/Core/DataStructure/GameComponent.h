#ifndef _GAMECOMPONENT_H_
#define _GAMECOMPONENT_H_

#include <string>
#include <vector>
#include <typeinfo>
#include <Vec2.h>
#include <Vec3.h>
#include <Mat4.h>

#include "Core/DLLHeader.h"
#include "Component.h"

namespace Quantix::Core::DataStructure
{
	class QUANTIX_API GameComponent
	{
	protected:
		#pragma region Attributes
		std::vector<Component*>		_component;
		std::string					_name;
		QXint						_layer;
		QXbool						_isStatic;
		QXbool						_isActive;
		#pragma endregion Attributes
	public:
		#pragma region Constructors/Destructor
		GameComponent() = default;
		GameComponent(const GameComponent& object) noexcept;
		GameComponent(GameComponent&& object) noexcept;
		GameComponent(std::string name, const QXbool& isStatic = false) noexcept;
		~GameComponent();
		#pragma endregion Constructors/Destructor

		#pragma region Methods

		/**
		 * @brief Clean Component that are destroyed
		 * 
		 */
		void					CleanDestroyedComponents();

		#pragma region Template
		/**
		 * @brief Add Component to the GameObject
		 * 
		 * @tparam T type of Component
		 */
		template<typename T>
		inline void				AddComponent()
		{
			T* comp = new T(this);
			_component.push_back(comp);
		}

		/**
		 * @brief Get the Component object
		 * 
		 * @tparam T type of the Component
		 * @return T* the component of that type
		 */
		template<typename T>
		inline T*				GetComponent()
		{
			const std::type_info& type = typeid(T&);
			for (Component* comp : _component)
			{
				if (comp->GetType() == type)
					return dynamic_cast<T*>(comp);
			}
			return nullptr;
		}

		/**
		 * @brief Get the Components object
		 * 
		 * @tparam T type of the Component
		 * @return std::vector<T*> components of that type
		 */
		template<typename T>
		inline std::vector<T*>	GetComponents()
		{
			std::vector<T*>			vecT;
			const std::type_info&	type = typeid(T&);
			for (Component* comp : _component)
			{
				if (comp->GetType() == type)
					vecT.push_back(comp);
			}
			return vecT;
		}

		/**
		 * @brief Remove component
		 * 
		 * @tparam T Component
		 * @param component Component you want to remove
		 */
		template<typename T>
		inline void				RemoveComponent(T* component)
		{
			for (auto it{ _component.begin() }; it != _component.end(); ++it)
			{
				if (*it == component)
				{
					(*it)->EraseEndOfFrame();
					return;
				}
			}
		}

		/**
		 * @brief Remove multiple components
		 * 
		 * @tparam T type of component you want to remove
		 */
		template<typename T>
		inline void				RemoveComponents()
		{
			const std::type_info& type{ typeid(T&) };

			for (unsigned i{ 0 }; i < _component.size(); ++i)
			{
				if (_component[i]->GetType() == type)
				{
					_component[i]->EraseEndOfFrame();
				}
			}
		}
		#pragma endregion Template

		#pragma region Accessors
		inline void				SetIsActive(QXbool IsActive) { _isActive = IsActive; };

		inline QXbool			GetIsActive() const { return _isActive; };

		inline QXstring			GetName() const { return _name; };

		/**
		 * @brief Set the Is Static object
		 * 
		 * @param IsStatic QXbool
		 */
		inline void				SetIsStatic(QXbool IsStatic) { _isStatic = IsStatic; };

		/**
		 * @brief Get the Is Static object
		 * 
		 * @return QXbool 
		 */
		inline QXbool			GetIsStatic() const { return _isStatic; };

		/**
		 * @brief Set the Layer object
		 * 
		 * @param layer QXint
		 */
		inline void				SetLayer(QXint layer) { _layer = layer; };

		/**
		 * @brief Get the Layer object
		 * 
		 * @return QXint 
		 */
		inline QXint			GetLayer() const { return _layer; };
		#pragma endregion Accessors
		GameComponent&			operator=(const GameComponent& gc);
		#pragma endregion Methods
	};
}

#endif // !_GAMEOBJECT_H_