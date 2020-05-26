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

	Renderer::Renderer(Platform::AppInfo& info, DataStructure::ResourcesManager& manager) noexcept :
		_projLight { Math::QXmat4::CreateOrthographicProjectionMatrix(20, 20, 1.0f, 7.5f) }
	{
		InitUnidirectionnalShadowBuffer();
		InitOmnidirectionnalShadowBuffer();

		_cube = manager.CreateModel("media/Mesh/cube.obj");
		_sphere = manager.CreateModel("media/Mesh/sphere.obj");
		_caps = manager.CreateModel("media/Mesh/capsule.obj");
		_wireFrameProgram = manager.CreateShaderProgram("../QuantixEngine/Media/Shader/Wireframe.vert", "../QuantixEngine/Media/Shader/Wireframe.frag");

		_shadowProgram = manager.CreateShaderProgram("../QuantixEngine/Media/Shader/Shadow.vert", "../QuantixEngine/Media/Shader/Shadow.frag");

		// Create uniform buffers
		glGenBuffers(1, &_viewProjMatrixUBO);
		glBindBuffer(GL_UNIFORM_BUFFER, _viewProjMatrixUBO);
		glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(Math::QXmat4), nullptr, GL_STATIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);

		glGenBuffers(1, &_viewProjShadowMatrixUBO);
		glBindBuffer(GL_UNIFORM_BUFFER, _viewProjShadowMatrixUBO);
		glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(Math::QXmat4), nullptr, GL_STATIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
		
		glGenBuffers(1, &_lightUBO);
		glBindBuffer(GL_UNIFORM_BUFFER, _lightUBO);
		glBufferData(GL_UNIFORM_BUFFER, 10 * sizeof(Core::Components::Light) + sizeof(QXuint), nullptr, GL_STATIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);

		// Set buffers binding
		glBindBufferBase(GL_UNIFORM_BUFFER, 0, _viewProjMatrixUBO);
		glBindBufferBase(GL_UNIFORM_BUFFER, 1, _viewProjShadowMatrixUBO);
		glBindBufferBase(GL_UNIFORM_BUFFER, 2, _lightUBO);

		InitPostProcessEffects(manager, info);
	}

	Renderer::~Renderer()
	{
		glDeleteFramebuffers(1, &_uniShadowBuffer.FBO);
		glDeleteFramebuffers(1, &_omniShadowBuffer.FBO);
		glDeleteBuffers(1, &_viewProjMatrixUBO);
		glDeleteBuffers(1, &_viewProjShadowMatrixUBO);
		glDeleteBuffers(1, &_lightUBO);
		delete _bloom;
		delete _effects;
	}

#pragma endregion

#pragma region Functions

	void Renderer::CreateRenderFramebuffer(QXuint width, QXuint height, RenderFramebuffer& fbo) noexcept
	{
		QXint previous_framebuffer;
        glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &previous_framebuffer);

        // Create Framebuffer that will hold 1 color attachement
		QXuint FBO;
        glGenFramebuffers(1, &FBO);
        glBindFramebuffer(GL_FRAMEBUFFER, FBO);

        // Create texture that will be used as color attachment
		QXuint texture[2];
        glGenTextures(2, texture);
        
		for (QXsizei i = 0; i < 2; ++i)
		{
			glBindTexture(GL_TEXTURE_2D, texture[i]);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + (GLenum)i, GL_TEXTURE_2D, texture[i], 0);
		}

		GLuint depth_stencil_renderbuffer;
		glGenRenderbuffers(1, &depth_stencil_renderbuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, depth_stencil_renderbuffer);
		glObjectLabel(GL_RENDERBUFFER, depth_stencil_renderbuffer, -1, "DepthStencilRenderbuffer");
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);

		// Setup attachements
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth_stencil_renderbuffer);

		QXuint draw_attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
        glDrawBuffers(2, draw_attachments);

        GLenum framebuffer_status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (framebuffer_status != GL_FRAMEBUFFER_COMPLETE)
        {
            LOG(ERROR, std::string("framebuffer failed to complete (0x%x)\n", framebuffer_status));
        }

        glBindFramebuffer(GL_FRAMEBUFFER, previous_framebuffer);

		fbo.FBO = FBO;
		fbo.texture[0] = texture[0];
		fbo.texture[1] = texture[1];
		fbo.depthBuffer = depth_stencil_renderbuffer;
	}

	void Renderer::CreateFramebuffer(QXuint width, QXuint height, Framebuffer& fbo) noexcept
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

		QXuint draw_attachments { GL_COLOR_ATTACHMENT0 };
		glDrawBuffers(1, &draw_attachments);

		GLenum framebuffer_status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (framebuffer_status != GL_FRAMEBUFFER_COMPLETE)
		{
			LOG(ERROR, std::string("framebuffer failed to complete (0x%x)\n", framebuffer_status));
		}

		glBindFramebuffer(GL_FRAMEBUFFER, previous_framebuffer);

		fbo.FBO = FBO;
		fbo.texture = texture;
		fbo.depthBuffer = depth_stencil_renderbuffer;
	}

	void Renderer::InitUnidirectionnalShadowBuffer() noexcept
	{
		const QXuint SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
		QXuint depthMapFBO;
		glGenFramebuffers(1, &depthMapFBO);
		// create depth texture
		QXuint depthMap;
		glGenTextures(1, &depthMap);
		glBindTexture(GL_TEXTURE_2D, depthMap);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		QXfloat borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
		// attach depth texture as FBO's depth buffer
		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);

		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		_uniShadowBuffer.FBO = depthMapFBO;
		_uniShadowBuffer.texture = depthMap;
	}

	void Renderer::InitOmnidirectionnalShadowBuffer() noexcept
	{
		const QXuint SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
		QXuint depthMapFBO;
		glGenFramebuffers(1, &depthMapFBO);
		// create depth texture
		QXuint depthMap;
		glGenTextures(1, &depthMap);
		glBindTexture(GL_TEXTURE_CUBE_MAP, depthMap);

		for (QXuint i = 0; i < 6; ++i)
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		QXfloat borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
		// attach depth texture as FBO's depth buffer
		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthMap, 0);

		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		_omniShadowBuffer.FBO = depthMapFBO;
		_omniShadowBuffer.texture = depthMap;
	}

	void Renderer::InitPostProcessEffects(DataStructure::ResourcesManager& manager, Platform::AppInfo& info) noexcept
	{
		// create Skybox effect
		_effects = new PostProcess::Skybox(manager.CreateShaderProgram("../QuantixEngine/Media/Shader/SkyboxShader.vert", "../QuantixEngine/Media/Shader/SkyboxShader.frag"),
			manager.CreateShaderProgram("../QuantixEngine/Media/Shader/CubemapShader.vert", "../QuantixEngine/Media/Shader/CubemapShader.frag"),
			manager.CreateModel("media/Mesh/cube.obj"), manager.CreateHDRTexture("media/Textures/skybox.hdr"));

		_bloom = new PostProcess::Bloom(manager.CreateShaderProgram("../QuantixEngine/Media/Shader/bloomBlur.vert", "../QuantixEngine/Media/Shader/Blur.frag"),
			manager.CreateShaderProgram("../QuantixEngine/Media/Shader/bloomBlur.vert", "../QuantixEngine/Media/Shader/Bloom.frag"),
			manager.CreateModel("media/Mesh/quad.obj"), info);

		_toneMapping = new PostProcess::ToneMapping(manager.CreateShaderProgram("../QuantixEngine/Media/Shader/ToneMapping.vert", "../QuantixEngine/Media/Shader/ToneMapping.frag"),
			manager.CreateModel("media/Mesh/quad.obj"), info);
	}

	QXuint Renderer::Draw(std::vector<Components::Mesh*>& mesh, std::vector<Components::ICollider*>& colliders, std::vector<Core::Components::Light>& lights,
		Core::Platform::AppInfo& info, Components::Camera* cam, RenderFramebuffer& buffer, bool displayColliders) noexcept
	{
		START_PROFILING("draw");

		std::sort(mesh.begin(), mesh.end(), [](const Components::Mesh* a, const Components::Mesh* b) {
			return a->key < b->key;
			});

		QXbyte last_shader_id = -1;
		QXbyte last_texture_id = -1;

		// Bind uniform buffer
		SendUniformBuffer(lights, info, cam);

		RenderShadows(mesh, info, lights);

		glBindFramebuffer(GL_FRAMEBUFFER, buffer.FBO);

		// Clear
		glClearColor(0.0f, 0.0f, 0.0f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);

		Resources::Material* material;
		DataStructure::GameObject3D* obj;

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
				material->SendData(_uniShadowBuffer.texture);
				last_texture_id = mesh[i]->textureID;
			}

			// Draw current mesh
			obj = (Quantix::Core::DataStructure::GameObject3D*)mesh[i]->GetObject();

			material->SetMat4("TRS", obj->GetTransform()->GetTRS());
			glBindVertexArray(mesh[i]->GetVAO());

			glDrawElements(GL_TRIANGLES, (GLsizei)mesh[i]->GetIndices().size(), GL_UNSIGNED_INT, 0);

			glBindVertexArray(0);
		}

		if (displayColliders)
		{
			RenderColliders(colliders);
		}

		_effects->Render(info, 0, 0, 0);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		_bloom->Render(info, buffer.texture[0], buffer.texture[1], buffer.FBO);

		STOP_PROFILING("draw");

		return buffer.texture[0];
	}
	
	void Renderer::RenderShadows(std::vector<Core::Components::Mesh*>& meshes, Quantix::Core::Platform::AppInfo& info,
		std::vector<Core::Components::Light>& lights)
	{
		_shadowProgram->Use();

		glBindFramebuffer(GL_FRAMEBUFFER, _uniShadowBuffer.FBO);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, 1024, 1024);

		QXbyte last_shader_id = -1;

		Quantix::Core::DataStructure::GameObject3D* obj;

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

		_shadowProgram->Unuse();
	}

	void Renderer::RenderColliders(std::vector<Components::ICollider*>& colliders)
	{
		_wireFrameProgram->Use();
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		Math::QXmat4					trs;
		DataStructure::GameObject3D*	obj;

		for (QXuint i = 0; i < colliders.size(); ++i)
		{
			obj = (Quantix::Core::DataStructure::GameObject3D*)colliders[i]->GetObject();
			trs = Math::QXmat4::CreateTRSMatrix(obj->GetGlobalPosition() + colliders[i]->GetPosition(), obj->GetLocalRotation() * colliders[i]->GetRotation(),
				colliders[i]->scale);

			glUniformMatrix4fv(_wireFrameProgram->GetLocation("TRS"), 1, false, trs.array);

			if (colliders[i]->typeShape == Components::ETypeShape::CUBE && _cube->IsReady())
			{
				glBindVertexArray(_cube->GetVAO());

				glDrawElements(GL_TRIANGLES, (GLsizei)_cube->GetIndices().size(), GL_UNSIGNED_INT, 0);

				glBindVertexArray(0);
			}
			else if (colliders[i]->typeShape == Components::ETypeShape::SPHERE && _sphere->IsReady())
			{
				glBindVertexArray(_sphere->GetVAO());

				glDrawElements(GL_TRIANGLES, (GLsizei)_sphere->GetIndices().size(), GL_UNSIGNED_INT, 0);

				glBindVertexArray(0);
			}
			else if (colliders[i]->typeShape == Components::ETypeShape::CAPSULE && _caps->IsReady())
			{
				glBindVertexArray(_caps->GetVAO());

				glDrawElements(GL_TRIANGLES, (GLsizei)_caps->GetIndices().size(), GL_UNSIGNED_INT, 0);

				glBindVertexArray(0);
			}
		}

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glActiveTexture(GL_TEXTURE0);
	}

	void Renderer::SendUniformBuffer(std::vector<Core::Components::Light>& lights, Core::Platform::AppInfo& info, Components::Camera* cam)
	{
		QXuint	light_size = (QXuint)lights.size();

		glBindBuffer(GL_UNIFORM_BUFFER, _viewProjMatrixUBO);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(Math::QXmat4), cam->GetLookAt().array);
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(Math::QXmat4), sizeof(Math::QXmat4), info.proj.array);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);

		glBindBuffer(GL_UNIFORM_BUFFER, _viewProjShadowMatrixUBO);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(Math::QXmat4),
			Math::QXmat4::CreateLookAtMatrix(lights[0].position, lights[0].position + lights[0].direction, Math::QXvec3::up).array);
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(Math::QXmat4), sizeof(Math::QXmat4), _projLight.array);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);

		glBindBuffer(GL_UNIFORM_BUFFER, _lightUBO);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(QXuint), &light_size);
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(QXuint) * 2, light_size * sizeof(Core::Components::Light), &lights[0]);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

#pragma endregion
}
