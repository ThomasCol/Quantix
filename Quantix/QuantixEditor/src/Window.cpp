#include "Window.h"

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

		_window = glfwCreateWindow(width, height, "Quantix Editor", nullptr, nullptr);

		if (_window == nullptr)
			throw std::runtime_error("Failed to create Window");

		glfwSetWindowUserPointer(_window, this);
		glfwMakeContextCurrent(_window);
		glfwSetWindowSizeCallback(_window, Resize);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))//gladLoadGL())
		{
			throw std::runtime_error("Failed to init openGL");
		}

		printf("GL_VERSION: %s\n", glGetString(GL_VERSION));
		printf("GL_VENDOR: %s\n", glGetString(GL_VENDOR));
		printf("GL_RENDERER: %s\n", glGetString(GL_RENDERER));
	}

	Window::Window(QXstring name, QXuint width, QXuint height) :
		_width{ width },
		_height{ height }
	{
		if (glfwInit() != QX_TRUE)
			throw std::runtime_error("Failed to create window");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		_window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);

		if (_window == nullptr)
			throw std::runtime_error("Failed to create Window");

		glfwSetWindowUserPointer(_window, this);
		glfwMakeContextCurrent(_window);
		glfwSetWindowSizeCallback(_window, Resize);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			throw std::runtime_error("Failed to init openGL");
		}
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