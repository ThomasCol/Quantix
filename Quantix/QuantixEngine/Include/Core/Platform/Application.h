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
		Quantix::Resources::Scene*		newScene{ nullptr };
		QXbool							sceneChange{ false };

#pragma endregion

#pragma region Constructors

		Application() = default;

		
		Application(QXuint width, QXuint height);

		/**
		 * @brief Destroy the Application object
		 */
		~Application();

#pragma endregion

#pragma region Functions

		/**
		 * @brief Run Application
		 */
		void Update(std::vector<Components::Mesh*>& meshes, std::vector<Components::ICollider*>& colliders,
			std::vector<Components::Light>& lights, QXbool isPlaying = false);

#pragma endregion
	};
}

#endif // __APPLICATION_H__
