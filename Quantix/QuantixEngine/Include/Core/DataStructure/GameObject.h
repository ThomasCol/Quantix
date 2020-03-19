#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include <string>
#include <vector>
#include <typeinfo>
//#include "Transform.h"
#include "Component.h"
#include <Vec3.h>
#include <Mat4.h>

namespace Core::DataStructure
{
	class GameObject
	{
	protected:
		#pragma region Attributes
	//	Transform					_tranform;
		std::vector<Component*>		_component;
		std::string					_name;
		QXint						_layer;
		QXbool						_isStatic;
		#pragma endregion Attributes
	public:
		#pragma region Constructors/Destructor
		GameObject() noexcept;
		GameObject(const GameObject& object) noexcept;
		GameObject(GameObject&& object) noexcept;
		GameObject(std::string name, const QXbool& isStatic = false) noexcept;
		~GameObject();
		#pragma endregion Constructors/Destructor

		#pragma region Methods
		/**
		 * @brief Add Child to a GameObject
		 * 
		 * @param object GameObject Child
		 */
		void					AddChild(GameObject* object);

		/**
		 * @brief Add Child to a GameObject
		 * 
		 * @param object const GameObject Child
		 */
		void					AddChild(const GameObject* object);

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

		/**
		 * @brief Set the Global Position object
		 * 
		 * @param pos QXvec3
		 */
		void					SetGlobalPosition(Math::QXvec3 pos);

		/**
		 * @brief Set the Global Rotation object
		 * 
		 * @param rot QXvec3
		 */
		void					SetGlobalRotation(Math::QXvec3 rot);

		/**
		 * @brief Get the Global Position object
		 * 
		 */
		//void					GetGlobalPosition() const { return _transform.GetGlobalPosition(); };

		/**
		 * @brief Get the Global Rotation object
		 * 
		 */
		//void					GetGlobalRotation() const { return _transform.GetGlobalRotation(); };

		/**
		 * @brief Set the Local Position object
		 * 
		 * @param pos QXvec3
		 */
		void					SetLocalPosition(Math::QXvec3 pos);

		/**
		 * @brief Set the Local Rotation object
		 * 
		 * @param rot QXvec3
		 */
		void					SetLocalRotation(Math::QXvec3 rot);

		/**
		 * @brief Set the Local Scale object
		 * 
		 * @param scale QXvec3
		 */
		void					SetLocalScale(Math::QXvec3 scale);

		/**
		 * @brief Get the Local Position object
		 * 
		 */
		//void					GetLocalPosition() const { return _transform.GetLocalPosition(); };

		/**
		 * @brief Get the Local Rotation object
		 * 
		 */
		//void					GetLocalRotation() const { return _transform.GetLocalRotation(); };

		/**
		 * @brief Get the Local Scale object
		 * 
		 */
		//void					GetLocalScale() const { return _transform.GetLocalScale(); };

		/**
		 * @brief Set the Transform object
		 * 
		 * @param mat QXmat4
		 */
		void					SetTransform(const Math::QXmat4& mat);

		/**
		 * @brief Set the Transform object
		 * 
		 * @param pos QXvec3
		 * @param rot QXvec3
		 * @param scale QXvec3
		 */
		void					SetTransform(const Math::QXvec3& pos, const Math::QXvec3& rot, const Math::QXvec3& scale);

		/**
		 * @brief Get the Transform object
		 * 
		 */
		//void					GetTransform() const { return _transform; };
		#pragma endregion Accessors
		#pragma endregion Methods
	};
}

#endif // !_GAMEOBJECT_H_