#include "Core/Render/Renderer.h"

#include <glad/glad.h>
#include <stdexcept>
#include <array>

#include "Core/Profiler/Profiler.h"
#include "Core/Render/PostProcess/Skybox.h"
#include "Core/DataStructure/ResourcesManager.h"
#include "Core/DataStructure/GameObject3D.h"

namespace Quantix::Core::Render
{
#pragma region Constructors

	Renderer::Renderer(QXuint width, QXuint height, DataStructure::ResourcesManager& manager) noexcept :
		_mainBuffer {}
	{
		CreateFrameBuffer(width, height);

		// Create uniform buffers
		glGenBuffers(1, &_viewProjMatrixUBO);
		glBindBuffer(GL_UNIFORM_BUFFER, _viewProjMatrixUBO);
		glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(Math::QXmat4), nullptr, GL_STATIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
		
		glGenBuffers(1, &_lightUBO);
		glBindBuffer(GL_UNIFORM_BUFFER, _lightUBO);
		glBufferData(GL_UNIFORM_BUFFER, 10 * sizeof(Core::Components::Light) + sizeof(QXuint), nullptr, GL_STATIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);

		// Set buffers binding
		glBindBufferBase(GL_UNIFORM_BUFFER, 0, _viewProjMatrixUBO);
		glBindBufferBase(GL_UNIFORM_BUFFER, 1, _lightUBO);

		InitPostProcessEffects(manager);

		glViewport(0, 0, width, height);

	}

#pragma endregion

#pragma region Functions

	void Renderer::CreateFrameBuffer(QXuint width, QXuint height) noexcept
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
            LOG(ERROR, std::string("framebuffer failed to complete (0x%x)\n", framebuffer_status));
        }

        glBindFramebuffer(GL_FRAMEBUFFER, previous_framebuffer);

        _mainBuffer.FBO = FBO;
        _mainBuffer.texture = texture;
		_mainBuffer.depthStencilRenderbuffer = depth_stencil_renderbuffer;
	}

	void Renderer::InitPostProcessEffects(DataStructure::ResourcesManager& manager) noexcept
	{
		// create Skybox effect
		_effects = new PostProcess::Skybox(manager.CreateShaderProgram("../QuantixEngine/Media/Shader/SkyboxShader.vert", "../QuantixEngine/Media/Shader/SkyboxShader.frag"),
			manager.CreateShaderProgram("../QuantixEngine/Media/Shader/CubemapShader.vert", "../QuantixEngine/Media/Shader/CubemapShader.frag"),
			manager.CreateModel("../QuantixEngine/Media/Mesh/cube.obj"), manager.CreateHDRTexture("../QuantixEngine/Media/Textures/skybox.hdr"));
	}

	QXuint Renderer::Draw(std::vector<Components::Mesh*>& mesh, std::vector<Core::Components::Light>& lights, Core::Platform::AppInfo& info, Components::Camera* cam) noexcept
	{
		START_PROFILING("draw");

		std::sort(mesh.begin(), mesh.end(), [](const Components::Mesh* a, const Components::Mesh* b) {
			return a->key < b->key;
		});

		QXbyte last_shader_id = -1;
		QXbyte last_texture_id = -1;
		QXuint	light_size = (QXuint)lights.size();

		glBindFramebuffer(GL_FRAMEBUFFER, _mainBuffer.FBO);

		// Clear
		glClearColor(0.0f, 0.0f, 0.0f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);

		// Bind uniform buffer
		{
			Math::QXmat4 proj{ Math::QXmat4::CreateProjectionMatrix(info.width, info.height, 0.1f, 1000.f, 80.f) };
			Math::QXmat4 view{ cam->GetLookAt() };

			glBindBuffer(GL_UNIFORM_BUFFER, _viewProjMatrixUBO);
			glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(Math::QXmat4), view.array);
			glBufferSubData(GL_UNIFORM_BUFFER, sizeof(Math::QXmat4), sizeof(Math::QXmat4), proj.array);
			glBindBuffer(GL_UNIFORM_BUFFER, 0);

			glBindBuffer(GL_UNIFORM_BUFFER, _lightUBO);
			glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(QXuint), &light_size);
			glBufferSubData(GL_UNIFORM_BUFFER, sizeof(QXuint) * 2, light_size * sizeof(Core::Components::Light), &lights[0]);
			glBindBuffer(GL_UNIFORM_BUFFER, 0);
		}

		Resources::Material* material;
		Math::QXmat4								trs;
		Quantix::Core::DataStructure::GameObject3D* obj;

		for (QXuint i = 0; i < mesh.size(); i++)
		{
			if (!mesh[i]->IsEnable())
				continue;
			material = mesh[i]->GetMaterial();

			// Compare Meshes key for binding each shader one time
			if (mesh[i]->shaderID != last_shader_id)
			{
				material->UseShader();
				material->SetFloat3("viewPos", cam->GetPos().e);
				last_shader_id = mesh[i]->shaderID;
			}

			// Compare Meshes key for binding each texture once per shader
			if (mesh[i]->textureID != last_texture_id)
			{
				material->SendData();
				last_texture_id = mesh[i]->textureID;
			}

			// Draw current mesh
			obj = (Quantix::Core::DataStructure::GameObject3D*)mesh[i]->GetObject();

			Math::QXmat4 trs = { obj->GetTransform()->GetTRS() };

			material->SetMat4("TRS", trs);

			glBindVertexArray(mesh[i]->GetVAO());

			glDrawElements(GL_TRIANGLES, (GLsizei)mesh[i]->GetIndices().size(), GL_UNSIGNED_INT, 0);

			glBindVertexArray(0);
		}

		glActiveTexture(0);
		_effects->Render(info);


		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		STOP_PROFILING("draw");

		return _mainBuffer.texture;
	}

#pragma endregion
}
