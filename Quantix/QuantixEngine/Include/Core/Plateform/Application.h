#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Core/Render/Renderer.h"
#include "Core/Plateform/Window.h"
#include "Core/Plateform/AppInfo.h"

namespace Quantix::Core::Plateform
{
	class QUANTIX_API Application
	{
	private:
#pragma region Attributes

		Window				_window;
		Render::Renderer 	_renderer;

#pragma endregion

	public:
#pragma region Attributes

		AppInfo info;

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
