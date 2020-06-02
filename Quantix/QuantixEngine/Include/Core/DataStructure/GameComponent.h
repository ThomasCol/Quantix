#ifndef _GAMECOMPONENT_H_
#define _GAMECOMPONENT_H_

#include <string>
#include <vector>
#include <Type.h>
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
	/**
	 * @brief enum Layer
	 * 
	 */
	enum class QUANTIX_API Layer
	{
		DEFAULT = (1 << 0),
		PLAYER = (1 << 1),
		SELECTABLE = (1 << 2),
		KILLZONE = (1 << 3),
		DESTRUCTIBLEMESH = (1 << 4)
	};

	/**
	 * @brief class GameComponent
	 * 
	 */
	class QUANTIX_API GameComponent
	{
	protected:
#pragma region Attributes
		std::vector<Component*>						_component;
		std::string									_name;
		Layer										_layer{ Layer::DEFAULT };
		QXbool										_isStatic { QX_FALSE };
		QXbool										_isActive{ QX_TRUE };
		QXbool										_toRender{ QX_FALSE };
		QXbool										_toUpdate{ QX_FALSE };
		QXbool										_toCollide{ QX_FALSE };
		QXbool										_is2D{ QX_FALSE };
		QXbool										_is3D{ QX_FALSE };
		#pragma endregion Attributes
	public:
		#pragma region Constructors/Destructor
		/**
		 * @brief Construct a new Game Component object
		 * 
		 */
		GameComponent() = default;

		/**
		 * @brief Construct a new Game Component object by copy
		 * 
		 * @param object 
		 */
		GameComponent(const GameComponent& object) noexcept;

		/**
		 * @brief Construct a new Game Component object by move
		 * 
		 * @param object 
		 */
		GameComponent(GameComponent&& object) noexcept;

		/**
		 * @brief Construct a new Game Component object
		 * 
		 * @param name 
		 * @param is2D 
		 * @param is3D 
		 * @param isStatic 
		 */
		GameComponent(const QXstring& name, const QXbool& is2D = QX_FALSE, const QXbool& is3D = QX_FALSE, const QXbool& isStatic = QX_FALSE) noexcept;

		/**
		 * @brief Destroy the Game Component object
		 * 
		 */
		~GameComponent() noexcept;
		#pragma endregion Constructors/Destructor

		#pragma region Methods

		/**
		 * @brief Clean Component that are destroyed
		 * 
		 */
		void					CleanDestroyedComponents() noexcept;

		#pragma region Template
		/**
		 * @brief Add Component to the GameObject
		 * 
		 * @tparam T type of Component
		 */
		template<typename T>
		inline T*				AddComponent() noexcept
		{
			T* comp = new T;
			_component.push_back(comp);
			return comp;
		}

		/**
		 * @brief Add Component with type of Component
		 * 
		 * @param comp 
		 */
		inline void		AddComponent(Quantix::Core::DataStructure::Component* comp) noexcept
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
		inline T*				GetComponent(QXbool usePolymorphism = false) noexcept
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
		inline std::vector<T*>	GetComponents(QXbool usePolymorphism = false) noexcept
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

		/**
		 * @brief Get the Components object
		 * 
		 * @return const std::vector<Component*>& 
		 */
		inline const std::vector<Component*>&	GetComponents() noexcept
		{
			return _component;
		}

		/**
		 * @brief Remove the Component
		 * 
		 * @param component 
		 */
		inline void				RemoveComponent(Component* component) noexcept
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

		/**
		 * @brief Virtual method Awake for the the GameObject
		 * 
		 */
		virtual void	Awake() {};

		/**
		 * @brief Virtual method Start for the the GameObject
		 * 
		 */
		virtual void	Start() {};

		/**
		 * @brief Virtual method Stop for the the GameObject
		 * 
		 */
		virtual void	Stop() {};

		/**
		 * @brief Update Method
		 * 
		 * @param meshes 
		 * @param colliders 
		 * @param lights 
		 * @param info 
		 * @param isPlaying 
		 */
		virtual void	Update(std::vector<Core::Components::Mesh*>& meshes, std::vector < Core::Components::ICollider* >& colliders,
								std::vector<Components::Light>& lights, Platform::AppInfo& info, QXbool isPlaying) {};

		/**
		 * @brief Destroy for the GameObject
		 * 
		 */
		virtual void	Destroy() {};

		#pragma endregion Template

		#pragma region Accessors
		/**
		 * @brief Get3D Object
		 * 
		 * @return QXbool 
		 */
		inline QXbool			Get3D() const  noexcept{ return _is3D; };

		/**
		 * @brief Set the Is Active object
		 * 
		 * @param IsActive 
		 */
		inline void				SetIsActive(QXbool IsActive)  noexcept{ _isActive = IsActive; };

		/**
		 * @brief Get the Is Active object
		 * 
		 * @return QXbool 
		 */
		inline QXbool			GetIsActive() const  noexcept{ return _isActive; };

		/**
		 * @brief Get the Name object
		 * 
		 * @return QXstring 
		 */
		inline QXstring			GetName() const  noexcept{ return _name; };

		/**
		 * @brief Set the Name object
		 * 
		 * @param name 
		 */
		inline void				SetName(QXstring name)  noexcept{ _name = name; };

		/**
		 * @brief Set the Is Static object
		 * 
		 * @param IsStatic QXbool
		 */
		inline void				SetIsStatic(QXbool IsStatic)  noexcept{ _isStatic = IsStatic; };

		/**
		 * @brief Get the Is Static object
		 * 
		 * @return QXbool 
		 */
		inline QXbool			GetIsStatic() const  noexcept{ return _isStatic; };

		/**
		 * @brief Set the Layer object
		 * 
		 * @param layer QXint
		 */
		inline void				SetLayer(Layer layer)  noexcept{ _layer = layer; };

		/**
		 * @brief Get the Layer object
		 * 
		 * @return QXint 
		 */
		inline Layer			GetLayer() const  noexcept{ return _layer; };


		/**
		 * @brief Set the Render object
		 *
		 * @param layer QXbool
		 */
		inline void				SetRender(QXbool render)  noexcept{ _toRender = render; };

		/**
		 * @brief Get the Render object
		 *
		 * @return QXbool
		 */
		inline QXbool			GetRender() const  noexcept{ return _toRender; };

		/**
		 * @brief Set the ToUpdate object
		 *
		 * @param update QXbool
		 */
		inline void				SetToUpdate(QXbool update)  noexcept{ _toUpdate = update; };

		/**
		 * @brief Get the ToUpdate object
		 *
		 * @return QXbool to update value
		 */
		inline QXbool			GetToUpdate() const  noexcept{ return _toUpdate; };

		#pragma endregion Accessors
		/**
		 * @brief operator by copy
		 * 
		 * @param gc 
		 * @return GameComponent& 
		 */
		GameComponent&			operator=(const GameComponent& gc) noexcept;
		#pragma endregion Methods

		CLASS_REGISTRATION();
	};
}

#endif // !_GAMEOBJECT_H_
