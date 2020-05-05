#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Core/Render/Renderer.h"
#include "Core/Platform/AppInfo.h"
#include "Core/DataStructure/ResourcesManager.h"
#include "Core/DataStructure/SceneManager.h"
#include "Resources/Scene.h"

namespace Quantix::Core::Platform
{
	class QUANTIX_API Application
	{
	private:
#pragma region Attributes

		

#pragma endregion

	public:
#pragma region Attributes

		AppInfo							info;
		DataStructure::ResourcesManager manager;
		Render::Renderer 				renderer;
		DataStructure::SceneManager		sceneManager;
		Resources::Scene*				scene;

#pragma endregion

#pragma region Constructors

		Application() = default;

		/**
		 * @brief Construct a new Application object
		 * 
		 * @param width Width of the window
		 * @param height Height of the window
		 */
		//Application(QXuint width, QXuint height);

		//Application(QXstring name, QXuint width, QXuint height);
		Application(QXuint width, QXuint height);

		/**
		 * @brief Destroy the Application object
		 */
		~Application() = default;

#pragma endregion

#pragma region Functions

		/**
		 * @brief Run Application
		 */
		void Update(std::vector<Core::Components::Mesh*>& meshes, std::vector<Components::ICollider*>& colliders, bool isPlaying = false);

#pragma endregion
	};
}

#endif // __APPLICATION_H__
