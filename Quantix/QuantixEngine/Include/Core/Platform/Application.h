#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Core/Render/Renderer.h"
#include "Core/Platform/AppInfo.h"
#include "Core/DataStructure/ResourcesManager.h"
#include "Resources/Scene.h"

namespace Quantix::Core::Platform
{
	class QUANTIX_API Application
	{
	private:
		#pragma region Attributes

		QXbool							_firstFrame { true };

		#pragma endregion

	public:
		#pragma region Attributes

		AppInfo							info;
		DataStructure::ResourcesManager manager;
		Render::Renderer 				renderer;
		Resources::Scene*				scene;
		Quantix::Resources::Scene*		newScene{ nullptr };
		QXbool							sceneChange{ false };

		#pragma endregion

		#pragma region Constructors

		/**
		 * @brief Construct a new Application object
		 * 
		 */
		Application() = default;

		/**
		 * @brief Construct a new Application object
		 * 
		 * @param width Width of window
		 * @param height Height of file
		 */
		Application(QXuint width, QXuint height) noexcept;

		/**
		 * @brief Destroy the Application object
		 */
		~Application() noexcept;

		#pragma endregion

		#pragma region Functions

		/**
		 * @brief Run Application
		 */
		void Update(std::vector<Components::Mesh*>& meshes, std::vector<Components::ICollider*>& colliders,
			std::vector<Components::Light>& lights, QXbool isPlaying = false) noexcept;

		#pragma endregion
	};
}

#endif // __APPLICATION_H__
