#ifndef __SCENE_H__
#define __SCENE_H__

#include "Core/DataStructure/GameObject3D.h"
#include "../Core/DataStructure/GameComponent.h"

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

			QXstring											_name;
			std::shared_ptr<Core::DataStructure::GameObject3D>	_root;
			QXuint												_id;

			std::vector<Core::DataStructure::GameObject3D*>		_objects;

			#pragma endregion

		public:

			#pragma region Constructors&Destructor

			/**
			 * @brief Construct a new Scene object
			 *
			 */
			Scene() = default;

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
			~Scene() = default;

			#pragma endregion

			#pragma region Methods

			#pragma region Functions

			Core::DataStructure::GameObject3D*	AddGameObject(const QXstring& name, const QXstring& parentName = "");

			/**
			 * @brief method that init the scene
			 *
			 */
			void	Init(Quantix::Core::DataStructure::ResourcesManager& manager);

			/**
			 * @brief method that update the world and its hierarchy
			 *
			 */
			void	Update(std::vector<Core::Components::Mesh*>& meshes);

			void Reset()noexcept;

			void Rename(const QXstring& str) noexcept;

			template<class Archive>
			void save(Archive& archive) const
			{
				archive(_name, _root->GetTransform(), _id);
			}

			template<class Archive>
			void load(Archive& archive)
			{
				archive(_name, _root->GetTransform(), _id);
			}

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

			const QXstring& GetName() noexcept { return _name; }

			const QXuint& GetID()const noexcept { return _id; }
			QXuint& GetID() noexcept { return _id; }

			inline std::shared_ptr<Core::DataStructure::GameObject3D> GetRoot() { return _root; }

			Core::DataStructure::GameObject3D* GetGameObject(const QXstring& name);

			#pragma endregion

			#pragma endregion
	};
}

#endif //__SCENE_H__