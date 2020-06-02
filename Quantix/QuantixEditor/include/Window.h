#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "glad/glad.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <functional>

#include <Type.h>
#include <Core/Platform/AppInfo.h>

namespace Quantix::Core::Platform
{
	class Window
	{
	private:
#pragma region Attributes

		GLFWwindow* 						_window;
		QXuint								_width;
		QXuint								_height;

#pragma endregion

#pragma region Functions

		/**
		 * @brief Resize callback for the window
		 * 
		 * @param window current window
		 * @param width New width
		 * @param height New height
		 */
		static void	Resize(GLFWwindow* window, QXint width, QXint height) noexcept;

#pragma endregion

	public:
#pragma region Contructors
		/**
		 * @brief Construct a new Window object
		 *
		 */
		Window() = default;

		/**
		 * @brief Construct a new Window object
		 *
		 * @param width Width of the window
		 * @param height Height of the window
		 */
		Window(QXuint width, QXuint height);

		/**
		 * @brief Construct a new Window object
		 *
		 * @param name
		 * @param width
		 * @param height
		 */
		Window(QXstring name, QXuint width, QXuint height);

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
		void		Refresh(AppInfo & info) noexcept;

		/**
		 * @brief Check if window should close
		 *
		 * @return true Window should close
		 * @return false Window shouldn't close
		 */
		inline bool ShouldClose()  noexcept { return glfwWindowShouldClose(_window); }



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
		 * @brief Get the Window object
		 * 
		 * @return GLFWwindow* 
		 */
		inline GLFWwindow* GetWindow() const { return _window; };

#pragma endregion

#pragma endregion
	};
}

#endif // __WINDOW_H__
