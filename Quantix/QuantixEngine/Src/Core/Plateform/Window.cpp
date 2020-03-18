#include "Core/Platform/Window.h"

#include <stdexcept>

namespace Quantix::Core::Platform
{
#pragma region Constructors

	Window::Window(QXuint width, QXuint height):
		_width {width},
		_height {height}
	{
		if (glfwInit() != QX_TRUE)
			throw std::runtime_error("Failed to create window");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		_window = glfwCreateWindow(width, height, "RendererDLL test", nullptr, nullptr);

		if (_window == nullptr)
			throw std::runtime_error("Failed to create Window");

		glfwSetWindowUserPointer(_window, this);
		glfwMakeContextCurrent(_window);
		glfwSetWindowSizeCallback(_window, Resize);
	}

	Window::~Window()
	{
		glfwDestroyWindow(_window);
		glfwTerminate();
	}

#pragma endregion

#pragma region Functions

	void Window::Resize(GLFWwindow* window, QXint width, QXint height)
	{
		Window* my_window = (Window*)glfwGetWindowUserPointer(window);
		
		my_window->_width = width;
		my_window->_height = height;

		my_window->_resizeCallback(width, height);
	}

	void Window::Refresh(AppInfo& info)
	{
		glfwPollEvents();
		glfwSwapBuffers(_window);
		info.currentTime = glfwGetTime();
		info.deltaTime = info.currentTime - info.prevTime;
		info.prevTime = info.currentTime;
	}

#pragma endregion
}