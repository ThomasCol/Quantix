#include "Core/Render/Renderer.h"

#include <stdexcept>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <functional>

namespace Quantix::Core::Render
{
	void ResizeCallback(QXuint width, QXuint height)
	{
		glViewport(0, 0, width, height);
	}

#pragma region Coonstructors

	Renderer::Renderer(QXuint width, QXuint height, std::function<void(QXuint, QXuint)>& resizeCallback)
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			throw std::runtime_error("Failed to init openGL");
		}

		glViewport(0, 0, width, height);
		glEnable(GL_CULL_FACE);

		resizeCallback = ResizeCallback;
	}

#pragma endregion

#pragma region Functions

	void Renderer::Draw(std::vector<Core::Components::Mesh*>& mesh, std::vector<Core::Components::Light*>& lights, Core::Plateform::AppInfo& info)
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (QXint i = 0; i < mesh.size(); ++i)
		{
			mesh[i]->SendDataToShader(info, lights);

			glBindVertexArray(mesh[i]->GetVAO());

			glDrawElements(GL_TRIANGLES, (GLsizei)mesh[i]->GetIndices().size(), GL_UNSIGNED_INT, 0);

			glBindVertexArray(0);
		}
	}

#pragma endregion
}