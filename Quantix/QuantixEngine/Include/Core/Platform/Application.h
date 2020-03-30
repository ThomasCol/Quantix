#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Core/Render/Renderer.h"
#include "Core/Platform/Window.h"
#include "Core/Platform/AppInfo.h"
#include "Core/DataStructure/ResourcesManager.h"

namespace Quantix::Core::Platform
{
	class QUANTIX_API Application
	{
	private:
#pragma region Attributes

		

#pragma endregion

	public:
#pragma region Attributes

		AppInfo info;
		Window							window;
		Render::Renderer 				renderer;
		DataStructure::ResourcesManager manager;

#pragma endregion

#pragma region Constructors

		/**
		 * @brief Construct a new Application object
		 * 
		 * @param width Width of the window
		 * @param height Height of the window
		 */
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
		void Run();

#pragma endregion
	};
}

#endif // __APPLICATION_H__
