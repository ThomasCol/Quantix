#include "Core/Render/Renderer.h"

#include <glad/glad.h>
#include <stdexcept>
#include <array>

#include "Core/Profiler/Profiler.h"
#include "Core/Render/PostProcess/Skybox.h"
#include "Core/DataStructure/ResourcesManager.h"
#include "Core/DataStructure/GameObject3D.h"
#include "Core/UserEntry/InputManager.h"

namespace Quantix::Core::Render
{
#pragma region Constructors

	Renderer::Renderer(QXuint width, QXuint height, DataStructure::ResourcesManager& manager) noexcept :
		_mainBuffer {}
	{
		CreateFrameBuffer(width, height);
		InitShadowBuffer();

		_shadowProgram = manager.CreateShaderProgram("../QuantixEngine/Media/Shader/Shadow.vert", "../QuantixEngine/Media/Shader/Shadow.frag");

		// Create uniform buffers
		glGenBuffers(1, &_viewProjMatrixUBO);
		glBindBuffer(GL_UNIFORM_BUFFER, _viewProjMatrixUBO);
		glBufferData(GL_UNIFORM_BUFFER, 4 * sizeof(Math::QXmat4), nullptr, GL_STATIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
		
		glGenBuffers(1, &_lightUBO);
		glBindBuffer(GL_UNIFORM_BUFFER, _lightUBO);
		glBufferData(GL_UNIFORM_BUFFER, 10 * sizeof(Core::Components::Light) + sizeof(QXuint), nullptr, GL_STATIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);

		// Set buffers binding
		glBindBufferBase(GL_UNIFORM_BUFFER, 0, _viewProjMatrixUBO);
		glBindBufferBase(GL_UNIFORM_BUFFER, 1, _lightUBO);

		InitPostProcessEffects(manager);
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
		_mainBuffer.depthBuffer = depth_stencil_renderbuffer;
	}

	void Renderer::InitShadowBuffer() noexcept
	{
		const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
		unsigned int depthMapFBO;
		glGenFramebuffers(1, &depthMapFBO);
		// create depth texture
		unsigned int depthMap;
		glGenTextures(1, &depthMap);
		glBindTexture(GL_TEXTURE_2D, depthMap);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
		// attach depth texture as FBO's depth buffer
		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);

		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		_shadowBuffer.FBO = depthMapFBO;
		_shadowBuffer.texture = depthMap;
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

		RenderShadows(mesh, info, lights);

		glBindFramebuffer(GL_FRAMEBUFFER, _mainBuffer.FBO);

		// Clear
		glClearColor(0.0f, 0.0f, 0.0f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);


		Math::QXmat4 proj = Math::QXmat4::CreateOrthographicProjectionMatrix(20.f, 20.f, 1.0f, 7.5f);
		Math::QXmat4 viewLight = Math::QXmat4::CreateLookAtMatrix(lights[0].position, {0, 0, 0}, Math::QXvec3::up);

		// Bind uniform buffer
		{
			Math::QXmat4 view = cam->GetLookAt();

			glBindBuffer(GL_UNIFORM_BUFFER, _viewProjMatrixUBO);
			glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(Math::QXmat4), view.array);
			glBufferSubData(GL_UNIFORM_BUFFER, sizeof(Math::QXmat4), sizeof(Math::QXmat4), info.proj.array);
			glBufferSubData(GL_UNIFORM_BUFFER, sizeof(Math::QXmat4) * 2, sizeof(Math::QXmat4), proj.array);
			glBufferSubData(GL_UNIFORM_BUFFER, sizeof(Math::QXmat4) * 3, sizeof(Math::QXmat4), viewLight.array);
			glBindBuffer(GL_UNIFORM_BUFFER, 0);

			glBindBuffer(GL_UNIFORM_BUFFER, _lightUBO);
			glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(QXuint), &light_size);
			glBufferSubData(GL_UNIFORM_BUFFER, sizeof(QXuint) * 2, light_size * sizeof(Core::Components::Light), &lights[0]);
			glBindBuffer(GL_UNIFORM_BUFFER, 0);
		}

		Resources::Material*						material;
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
				material->SendData(_shadowBuffer.texture);
				last_texture_id = mesh[i]->textureID;
			}

			// Draw current mesh
			obj = (Quantix::Core::DataStructure::GameObject3D*)mesh[i]->GetObject();

			material->SetMat4("TRS", obj->GetTransform()->GetTRS());

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

	void Renderer::RenderShadows(std::vector<Core::Components::Mesh*>& meshes, Quantix::Core::Platform::AppInfo& info,
		std::vector<Core::Components::Light>& lights)
	{
		_shadowProgram->Use();
		glCullFace(GL_FRONT);
		glBindFramebuffer(GL_FRAMEBUFFER, _shadowBuffer.FBO);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, 1024, 1024);

		QXbyte last_shader_id = -1;

		Quantix::Core::DataStructure::GameObject3D* obj;
		Math::QXmat4 proj = Math::QXmat4::CreateOrthographicProjectionMatrix(20.f, 20.f, 1.0f, 7.5f);
		Math::QXmat4 view = Math::QXmat4::CreateLookAtMatrix(lights[0].position, { 0, 0, 0 }, Math::QXvec3::up);

		LOG(INFOS, view.ToString());

		glUniformMatrix4fv(_shadowProgram->GetLocation("view"), 1, false, view.array);
		glUniformMatrix4fv(_shadowProgram->GetLocation("proj"), 1, false, proj.array);

		for (QXuint i = 0; i < meshes.size(); i++)
		{
			if (!meshes[i]->IsEnable())
				continue;

			obj = (Quantix::Core::DataStructure::GameObject3D*)meshes[i]->GetObject();

			glUniformMatrix4fv(_shadowProgram->GetLocation("model"), 1, false, obj->GetTransform()->GetTRS().array);

			glBindVertexArray(meshes[i]->GetVAO());

			glDrawElements(GL_TRIANGLES, (GLsizei)meshes[i]->GetIndices().size(), GL_UNSIGNED_INT, 0);

			glBindVertexArray(0);
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glViewport(0, 0, info.width, info.height);
		glCullFace(GL_BACK);
	}

#pragma endregion
}
