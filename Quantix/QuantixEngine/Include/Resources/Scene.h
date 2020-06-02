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
			Core::DataStructure::GameObject3D*					_root3D;
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
			Scene() noexcept;

			/**
			 * @brief Construct a new Scene object
			 * 
			 * @param name Name of the scene
			 * @param root Root object
			 * @param id id of the scene
			 */
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
			~Scene() noexcept;

			#pragma endregion

			#pragma region Methods

			#pragma region Functions

			/**
			 * @brief Add Game object to the scene
			 * 
			 * @param name name of the object
			 * @param parent parent object
			 * @return Core::DataStructure::GameObject3D* new gameObject
			 */
			Core::DataStructure::GameObject3D*	AddGameObject(const QXstring& name, void* parent = nullptr) noexcept;

			/**
			 * @brief Add Game object 2D to the scene
			 * 
			 * @param name name of the object
			 * @param parent parent object
			 * @return Core::DataStructure::GameObject2D* new gameObject
			 */
			Core::DataStructure::GameObject2D*	AddGameObject2D(const QXstring& name, void* parent = nullptr) noexcept;

			/**
			 * @brief Add game component to the scene
			 * 
			 * @param name name of the object
			 * @param parent parent object
			 * @return Core::DataStructure::GameComponent* new gameComponent
			 */
			Core::DataStructure::GameComponent*	AddGameComponent(const QXstring& name, void* parent = nullptr) noexcept;

			/**
			 * @brief Init scene
			 * 
			 * @param manager Manager to init scene
			 */
			void	Init(Quantix::Core::DataStructure::ResourcesManager& manager) noexcept;

			/**
			 * @brief Update scene
			 * 
			 * @param meshes meshes to render
			 * @param colliders colliders to use
			 * @param lights lights to render
			 * @param info App info
			 * @param isPlaying if is play mode
			 */
			void	Update(std::vector<Core::Components::Mesh*>& meshes, std::vector<Core::Components::ICollider*>& colliders,
				std::vector<Core::Components::Light>& lights, Core::Platform::AppInfo& info, QXbool isPlaying) noexcept;

			/**
			 * @brief Chack th destroy
			 * 
			 * @param info App info
			 */
			void CheckDestroy(Core::Platform::AppInfo& info) noexcept;

			/**
			 * @brief Start the scene
			 * 
			 */
			void	Start() noexcept;

			/**
			 * @brief Stop the scene
			 * 
			 */
			void	Stop() noexcept;

			/**
			 * @brief Reset the scene
			 * 
			 */
			void Reset() noexcept;

			/**
			 * @brief Rename the scene
			 * 
			 * @param str 
			 */
			void Rename(const QXstring& str) noexcept;

			/**
			 * @brief Find game component on scene
			 * 
			 * @param gc Game component to find
			 * @return QXbool true is in the scene false is not
			 */
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

			/**
			 * @brief Get the Name object
			 * 
			 * @return const QXstring& name of the scene
			 */
			const QXstring&											GetName() noexcept { return _name; }

			/**
			 * @brief Get scene ID
			 * 
			 * @return const QXuint& ID
			 */
			const QXuint&											GetID()const noexcept { return _id; }

			/**
			 * @brief Get scene ID
			 * 
			 * @return QXuint& scene id
			 */
			QXuint&													GetID() noexcept { return _id; }

			/**
			 * @brief Get the Root object
			 * 
			 * @return Core::DataStructure::GameObject3D* Root
			 */
			inline Core::DataStructure::GameObject3D*				GetRoot() noexcept { return _root3D; }

			/**
			 * @brief Get the Root 2 D object
			 * 
			 * @return Core::DataStructure::GameObject2D*  root
			 */
			inline Core::DataStructure::GameObject2D*				GetRoot2D() noexcept { return _root2D; }

			/**
			 * @brief Get the Root Game Component object
			 * 
			 * @return Core::DataStructure::GameComponent* root
			 */
			inline Core::DataStructure::GameComponent*				GetRootGameComponent() noexcept { return _rootComponent; }

			/**
			 * @brief Get the Game Objects 3 D object
			 * 
			 * @return std::vector<Core::DataStructure::GameObject3D*> objects
			 */
			inline std::vector<Core::DataStructure::GameObject3D*>	GetGameObjects3D() noexcept { return _objects; }

			/**
			 * @brief Get the Game Objects 2 D object
			 * 
			 * @return std::vector<Core::DataStructure::GameObject2D*> objects
			 */
			inline std::vector<Core::DataStructure::GameObject2D*>	GetGameObjects2D() noexcept { return _objects2D; }

			/**
			 * @brief Get the Game Components object
			 * 
			 * @return std::list<Core::DataStructure::GameComponent*>& objects
			 */
			inline std::list<Core::DataStructure::GameComponent*>&	GetGameComponents() noexcept { return _objectsComponent; }

			/**
			 * @brief Get the Game Object object
			 * 
			 * @param name name of the object
			 * @return Core::DataStructure::GameObject3D* object
			 */
			Core::DataStructure::GameObject3D*						GetGameObject(const QXstring& name) noexcept;

			/**
			 * @brief Get the Game Object 2 D object
			 * 
			 * @param name name of the object
			 * @return Core::DataStructure::GameObject2D* object
			 */
			Core::DataStructure::GameObject2D*						GetGameObject2D(const QXstring& name) noexcept;

			/**
			 * @brief Is scene ready
			 * 
			 * @return QXbool true ready false not
			 */
			inline QXbool											IsReady() const noexcept { return _isReady.load(); }

			/**
			 * @brief Set the Ready object
			 * 
			 * @param ready true ready false not ready
			 */
			inline void												SetReady(QXbool ready) noexcept { _isReady.store(ready); }

			#pragma endregion

			#pragma endregion
	};
}

#endif //__SCENE_H__
