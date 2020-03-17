#ifndef __WINDOW_H__
#define __WINDOW_H__

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <functional>

#include "Core/Type.h"
#include "Core/DLLHeader.h"
#include "Core/Plateform/AppInfo.h"

namespace Quantix::Core::Plateform
{
	class QUANTIX_API Window
	{
	private:
#pragma region Attributes

		GLFWwindow* 						_window;
		QXuint								_width;
		QXuint								_height;
		std::function<void(QXuint, QXuint)>	_resizeCallback;

#pragma endregion

#pragma region Functions

		/**
		 * @brief Resize callback for the window
		 * 
		 * @param window current window
		 * @param width New width
		 * @param height New height
		 */
		static void	Resize(GLFWwindow* window, QXint width, QXint height);

#pragma endregion

	public:
#pragma region Contructors

		/**
		 * @brief Construct a new Window object
		 * 
		 * @param width Width of the window
		 * @param height Height of the window
		 */
		Window(QXuint width, QXuint height);

		/**
		 * @brief Destroy the Window object
		 */
		~Window();

#pragma endregion

#pragma region Functions

		/**
		 * @brief Refresh the window
		 * 
		 */
		void		Refresh(AppInfo& info);

		/**
		 * @brief Check if window should close
		 * 
		 * @return true Window should close
		 * @return false Window shouldn't close
		 */
		inline bool ShouldClose() { return glfwWindowShouldClose(_window); }



#pragma region Accessors


		/**
		 * @brief Get the height of the window
		 * 
		 * @return const QXuint& height value
		 */
		inline const QXuint& GetHeight() const  { return _height; }

		/**
		 * @brief Get the width of the window
		 * 
		 * @return const QXuint& width value
		 */
		inline const QXuint& GetWidth() const  { return _width; }

		/**
		 * @brief Get the Resize Callback object
		 * 
		 * @return std::function<void(QXuint, QXuint)>& Return function ptr to bind it
		 */
		inline std::function<void(QXuint, QXuint)>&	GetResizeCallback() { return _resizeCallback; }

#pragma endregion

#pragma endregion
	};
}

#endif // __WINDOW_H__
