#ifndef __SCENE_H__
#define __SCENE_H__

#include "Core/DataStructure/GameObject2D.h"
#include "Core/DataStructure/GameObject3D.h"
#include "Core/Components/Collider.h"
#include "Core/Platform/AppInfo.h"

namespace Quantix::Core::DataStructure
{
	class ResourcesManager;
}

namespace Quantix::Resources
{
	class QUANTIX_API Scene
	{
		private:

			#pragma region Attributes

			QXstring											_name = "Default";
			Core::DataStructure::GameComponent*					_rootComponent;
			Core::DataStructure::GameObject2D*					_root2D;
			Core::DataStructure::GameObject3D*					_root;
			QXuint												_id;

			std::list<Core::DataStructure::GameComponent*>		_objectsComponent;
			std::vector<Core::DataStructure::GameObject2D*>		_objects2D;
			std::vector<Core::DataStructure::GameObject3D*>		_objects;
			
			std::atomic_bool									_isReady { false };

			#pragma endregion

		public:

			#pragma region Constructors&Destructor

			/**
			 * @brief Construct a new Scene object
			 *
			 */
			Scene();

			Scene(const QXstring& name, Core::DataStructure::GameObject3D* root, const QXuint& id) noexcept;

			/**
			 * @brief Construct a new Scene object by copy
			 *
			 * @param copy Scene
			 */
			Scene(const Scene& copy) noexcept;

			/**
			 * @brief Construct a new Scene object by move
			 *
			 * @param copy Scene
			 */
			Scene(Scene&& copy) noexcept;

			/**
			 * @brief Destroy the Scene object
			 *
			 */
			~Scene();

			#pragma endregion

			#pragma region Methods

			#pragma region Functions

			Core::DataStructure::GameObject3D*	AddGameObject(const QXstring& name, void* parent = nullptr);
			Core::DataStructure::GameObject2D*	AddGameObject2D(const QXstring& name, void* parent = nullptr);
			Core::DataStructure::GameComponent*	AddGameComponent(const QXstring& name, void* parent = nullptr);

			/**
			 * @brief method that init the scene
			 *
			 */
			void	Init(Quantix::Core::DataStructure::ResourcesManager& manager) noexcept;

			/**
			 * @brief method that update the world and its hierarchy
			 *
			 */
			void	Update(std::vector<Core::Components::Mesh*>& meshes, std::vector<Core::Components::ICollider*>& colliders, Core::Platform::AppInfo& info) noexcept;

			void	Start() noexcept;

			void Reset()noexcept;

			void Rename(const QXstring& str) noexcept;

			QXbool	FindGameComponent(Core::DataStructure::GameComponent* gc) noexcept;

			#pragma endregion

			#pragma region Operators

			/**
			 * @brief Operator = for the scene
			 *
			 * @param s Scene to copy
			 * @return Scene& Reference to the current scene
			 */
			Scene& operator=(const Scene& s) noexcept;

			/**
			 * @brief Operator = for the scene
			 *
			 * @param s Scene to copy
			 * @return Scene& Reference to the current scene
			 */
			Scene& operator=(Scene&& s) noexcept;

			#pragma endregion

			#pragma region Accessors

			const QXstring&											GetName() noexcept { return _name; }

			const QXuint&											GetID()const noexcept { return _id; }
			QXuint&													GetID() noexcept { return _id; }

			inline Core::DataStructure::GameObject3D*				GetRoot() { return _root; }
			inline Core::DataStructure::GameObject2D*				GetRoot2D() { return _root2D; }
			inline Core::DataStructure::GameComponent*				GetRootGameComponent() { return _rootComponent; }
			inline std::vector<Core::DataStructure::GameObject3D*>	GetGameObjects3D() { return _objects; }
			inline std::vector<Core::DataStructure::GameObject2D*>	GetGameObjects2D() { return _objects2D; }
			inline std::list<Core::DataStructure::GameComponent*>&	GetGameComponents() { return _objectsComponent; }

			Core::DataStructure::GameObject3D*						GetGameObject(const QXstring& name) noexcept;
			Core::DataStructure::GameObject2D*						GetGameObject2D(const QXstring& name) noexcept;

			inline QXbool											IsReady() const { return _isReady.load(); }

			inline void												SetReady(QXbool ready) { _isReady.store(ready); }

			#pragma endregion

			#pragma endregion
	};
}

#endif //__SCENE_H__
