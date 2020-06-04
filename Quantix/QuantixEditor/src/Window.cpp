#include "Window.h"

#include <stdexcept>

extern "C"
{
	__declspec(dllexport) int NvOptimusEnablement = 1;
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

namespace Quantix::Core::Platform
{

	void OpenGLErrorCallback(GLenum Source, GLenum Type, GLuint Id, GLenum Severity, GLsizei Length, const GLchar* Message, const void* UserParam) noexcept
	{
		fprintf(stderr, "OpenGL log (0x%x): %s\n", Id, Message);
	}
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

		glfwMakeContextCurrent(_window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			throw std::runtime_error("Failed to init openGL");
		}

		glDebugMessageCallback(OpenGLErrorCallback, nullptr);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);


		printf("GL_VERSION: %s\n", glGetString(GL_VERSION));
		printf("GL_VENDOR: %s\n", glGetString(GL_VENDOR));
		printf("GL_RENDERER: %s\n", glGetString(GL_RENDERER));

		glfwSetWindowUserPointer(_window, reinterpret_cast<void*>(this));

		Window* my_window = (Window*)glfwGetWindowUserPointer(_window);
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

		glfwMakeContextCurrent(_window);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			throw std::runtime_error("Failed to init openGL");
		}
		glfwSetWindowUserPointer(_window, reinterpret_cast<void*>(this));

		Window* my_window = (Window*)glfwGetWindowUserPointer(_window);

	}

	Window::~Window() noexcept
	{
		glfwDestroyWindow(_window);
		glfwTerminate();
	}

#pragma endregion

#pragma region Functions

	void Window::Resize(GLFWwindow* window, QXint width, QXint height) noexcept
	{
		_width = width;
		_height = height;

		_event.Raise(window, width, height);

		glViewport(0, 0, width, height);

	}

	void Window::Refresh(AppInfo& info) noexcept
	{
		glfwPollEvents();
		glfwSwapBuffers(_window);
		info.currentTime = glfwGetTime();
		info.deltaTime = info.currentTime - info.prevTime;
		info.prevTime = info.currentTime;

		QXint width, height;

		glfwGetFramebufferSize(_window, &width, &height);

		if (width != _width || height != _height)
			Resize(_window, width, height);
	}

#pragma endregion
}