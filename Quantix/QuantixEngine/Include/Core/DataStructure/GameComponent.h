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
#include "Core/Components/Mesh.h"
#include "Core/Components/Behaviour.h"
#include "Core/Components/Collider.h"

namespace Quantix::Core::DataStructure
{
	class QUANTIX_API GameComponent
	{
	protected:
#pragma region Attributes
		std::vector<Component*>						_component;
		std::string									_name		{ "" };
		QXint										_layer		{ -1 };
		QXbool										_isStatic	{ false };
		QXbool										_isActive	{ true };
		QXbool										_toRender	{ false };
		QXbool										_toUpdate	{ false };
		QXbool										_toCollide	{ false };
		#pragma endregion Attributes
	public:
		#pragma region Constructors/Destructor
		GameComponent() = default;
		GameComponent(const GameComponent& object) noexcept;
		GameComponent(GameComponent&& object) noexcept;
		GameComponent(const QXstring& name, const QXbool& isStatic = false) noexcept;
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
		inline T*				AddComponent()
		{
			T* comp = new T;
			_component.push_back(comp);
			return comp;
		}

		inline void		AddComponent(Quantix::Core::DataStructure::Component* comp)
		{
			_component.push_back(comp);
		}

		/**
		 * @brief Get the Component object
		 * 
		 * @tparam T type of the Component
		 * @return T* the component of that type
		 */
		template<typename T>
		inline T*				GetComponent(QXbool usePolymorphism = false)
		{
			if (!usePolymorphism)
			{
				for (Component* comp : _component)
				{
					rttr::type t = comp->get_type();

					if (rttr::type::get<T>() == t)
						return dynamic_cast<T*>(comp);
				}
			}
			else
			{
				for (Component* comp : _component)
				{
					rttr::type t = comp->get_type();

					if (rttr::type::get<T>().is_base_of(t))
						return dynamic_cast<T*>(comp);
				}
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
		inline std::vector<T*>	GetComponents(QXbool usePolymorphism = false)
		{
			std::vector<T*>			vecT; 
			if (!usePolymorphism)
			{
				for (Component* comp : _component)
				{
					rttr::type t = comp->get_type();

					if (rttr::type::get<T>() == t)
						vecT.push_back(dynamic_cast<T*>(comp));
				}
			}
			else
			{
				for (Component* comp : _component)
				{
					rttr::type t = comp->get_type();

					if (rttr::type::get<T>().is_base_of(t))
						vecT.push_back(dynamic_cast<T*>(comp));
				}
			}
			return vecT;
		}

		inline const std::vector<Component*>&	GetComponents()
		{
			return _component;
		}

		inline void				RemoveComponent(Component* component)
		{
			for (auto it{_component.begin()}; it != _component.end(); ++it)
			{
				if ((*it) == component)
				{
					(*it)->EraseEndOfFrame();
					(*it)->Destroy();
					_component.erase(it);
					return;
				}
			}
		}

		virtual void Awake() {};
		virtual void Start() {};
		virtual void Update(std::vector<Core::Components::Mesh*>& meshes, std::vector < Core::Components::ICollider* >& colliders, Platform::AppInfo& info) {};

		#pragma endregion Template

		#pragma region Accessors
		inline void				SetIsActive(QXbool IsActive) { _isActive = IsActive; };

		inline QXbool			GetIsActive() const { return _isActive; };

		inline QXstring			GetName() const { return _name; };

		inline void				SetName(QXstring name) { _name = name; };

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
		 * @brief Set the Render object
		 *
		 * @param layer QXbool
		 */
		inline void				SetRender(QXbool render) { _toRender = render; };

		/**
		 * @brief Get the Render object
		 *
		 * @return QXbool
		 */
		inline QXbool			GetRender() const { return _toRender; };

		/**
		 * @brief Set the ToUpdate object
		 *
		 * @param update QXbool
		 */
		inline void				SetToUpdate(QXbool update) { _toUpdate = update; };

		/**
		 * @brief Get the ToUpdate object
		 *
		 * @return QXbool to update value
		 */
		inline QXbool			GetToUpdate() const { return _toUpdate; };

		#pragma endregion Accessors
		GameComponent&			operator=(const GameComponent& gc);
		#pragma endregion Methods

		CLASS_REGISTRATION();
	};
}

#endif // !_GAMEOBJECT_H_
