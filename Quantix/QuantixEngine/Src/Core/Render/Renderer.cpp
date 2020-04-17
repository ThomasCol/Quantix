#include "Core/Render/Renderer.h"

#include <glad/glad.h>

#include <stdexcept>
#include <array>

#include "Core/DataStructure/GameObject3D.h"

namespace Quantix::Core::Render
{
	void ResizeCallback(QXuint width, QXuint height)
	{
		glViewport(0, 0, width, height);
	}

#pragma region Constructors

	Renderer::Renderer(QXuint width, QXuint height, std::function<void(QXuint, QXuint)>& resizeCallback) :
		_mainBuffer {}
	{
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

		GLuint depth_stencil_renderbuffer;
		glGenRenderbuffers(1, &depth_stencil_renderbuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, depth_stencil_renderbuffer);
		glObjectLabel(GL_RENDERBUFFER, depth_stencil_renderbuffer, -1, "DepthStencilRenderbuffer");
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);

		// Setup attachements
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth_stencil_renderbuffer);

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
		_mainBuffer.depthStencilRenderbuffer = depth_stencil_renderbuffer;
	}

	void Renderer::BindShader(Resources::Material* material, Core::Platform::AppInfo& info, Components::Camera* cam, std::vector<Core::Components::Light*>& lights)
	{
		Math::QXmat4 proj{ Math::QXmat4::CreateProjectionMatrix(info.width, info.height, 0.1f, 1000.f, 80.f) };
		Math::QXmat4 view{ cam->GetLookAt() };

		material->UseShader();

		material->SetMat4("proj", proj);
		material->SetMat4("view", view);
		material->SetFloat3("viewPos", cam->GetPos().e);

		material->SetLightArray(lights);
	}

	QXuint Renderer::Draw(std::vector<Components::Mesh*>& mesh, std::vector<Core::Components::Light*>& lights, Core::Platform::AppInfo& info, Components::Camera* cam)
	{
		std::sort(mesh.begin(), mesh.end(), [](const Components::Mesh* a, const Components::Mesh* b) {
			return a->key < b->key;
		});

		QXbyte last_shader_id = -1;
		QXbyte last_texture_id = -1;

		glBindFramebuffer(GL_FRAMEBUFFER, _mainBuffer.FBO);

		glClearColor(0.0f, 0.0f, 0.0f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);

		Resources::Material* material;

		for (QXuint i = 0; i < mesh.size(); i++)
		{
			if (!mesh[i]->IsEnable())
				continue;
			material = mesh[i]->GetMaterial();

			if (mesh[i]->shaderID != last_shader_id)
			{
				BindShader(material, info, cam, lights);
				last_shader_id = mesh[i]->shaderID;
			}

			if (mesh[i]->textureID != last_texture_id)
			{
				material->SendData();
				last_texture_id = mesh[i]->textureID;
			}

			Quantix::Core::DataStructure::GameObject3D* obj = (Quantix::Core::DataStructure::GameObject3D*)mesh[i]->GetObject();

			Math::QXmat4 trs = { obj->GetTransform()->GetTRS() };

			material->SetMat4("TRS", trs);

			glBindVertexArray(mesh[i]->GetVAO());

			glDrawElements(GL_TRIANGLES, (GLsizei)mesh[i]->GetIndices().size(), GL_UNSIGNED_INT, 0);

			glBindVertexArray(0);
		}

		glActiveTexture(0);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		return _mainBuffer.texture;
	}

#pragma endregion
}
