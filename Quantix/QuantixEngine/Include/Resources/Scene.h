#ifndef __SCENE_H__
#define __SCENE_H__

#include "Physic/Transform3D.h"
#include "../Core/DataStructure/GameComponent.h"

namespace Quantix::Resources
{
	class Scene
	{
		private:

			#pragma region Attributes

			QXstring			_name;
			Physic::Transform3D	_world;
			QXuint		_id;

			#pragma endregion

		public:

			#pragma region Constructors&Destructor

			/**
			 * @brief Construct a new Scene object
			 *
			 */
			Scene() = default;

			Scene(const QXstring& name, const Physic::Transform3D& world, const QXuint& id) noexcept;

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

			/**
			 * @brief method that init the scene
			 *
			 */
			void	Init();

			/**
			 * @brief method that update the world and its hierarchy
			 *
			 */
			void	Update();

			void Reset()noexcept;

			void Rename(const QXstring& str) noexcept;

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

			#pragma endregion

			#pragma endregion
	};
}

#endif //__SCENE_H__