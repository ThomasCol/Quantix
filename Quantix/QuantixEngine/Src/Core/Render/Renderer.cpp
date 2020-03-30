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

	Renderer::Renderer(QXuint width, QXuint height, std::function<void(QXuint, QXuint)>& resizeCallback) :
		_mainBuffer {}
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			throw std::runtime_error("Failed to init openGL");
		}

		glViewport(0, 0, width, height);

		resizeCallback = ResizeCallback;

		CreateFrameBuffer(width, height);
	}

#pragma endregion

#pragma region Functions

	void Renderer::CreateFrameBuffer(QXuint width, QXuint height)
	{
		QXint previous_framebuffer;
        glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &previous_framebuffer);

        // Create Framebuffer that will hold 1 color attachement
		QXuint FBO;
        glGenFramebuffers(1, &FBO);
        glBindFramebuffer(GL_FRAMEBUFFER, FBO);

        // Create texture that will be used as color attachment
		QXuint texture;
        glGenTextures(1, &texture);
        
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

        QXuint draw_attachments = GL_COLOR_ATTACHMENT0;
        glDrawBuffers(1, &draw_attachments);

        GLenum framebuffer_status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (framebuffer_status != GL_FRAMEBUFFER_COMPLETE)
        {
            fprintf(stderr, "demo_bloom::framebuffer failed to complete (0x%x)\n", framebuffer_status);
        }

        glBindFramebuffer(GL_FRAMEBUFFER, previous_framebuffer);

        _mainBuffer.FBO = FBO;
        _mainBuffer.texture = texture;
	}

	QXuint Renderer::Draw(std::vector<Core::Components::Mesh*>& mesh, std::vector<Core::Components::Light*>& lights, Core::Platform::AppInfo& info)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, _mainBuffer.FBO);

		glClearColor(0.0f, 0.0f, 0.0f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);

		for (QXint i = 0; i < mesh.size(); ++i)
		{
			mesh[i]->SendDataToShader(info, lights);

			glBindVertexArray(mesh[i]->GetVAO());

			glDrawElements(GL_TRIANGLES, (GLsizei)mesh[i]->GetIndices().size(), GL_UNSIGNED_INT, 0);

			glBindVertexArray(0);
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		return _mainBuffer.texture;
	}

#pragma endregion
}