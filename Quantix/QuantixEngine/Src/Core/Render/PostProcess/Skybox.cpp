#include "Core/Render/PostProcess/Skybox.h"

#include <glad/glad.h>
#include <Mat4.h>

#include "Core/Debugger/Logger.h"

namespace Quantix::Core::Render::PostProcess
{
	Skybox::Skybox(Resources::ShaderProgram* backgroundProgram, Resources::ShaderProgram* cubemapShader, Resources::Model* quadModel, Resources::Texture* skyTexture) noexcept :
		PostProcessEffect(backgroundProgram, quadModel),
		_cubemapProgram { cubemapShader },
		_skyboxTexture {skyTexture}
	{
		enable = true;
		name = "Skybox";
		Init();
	}

	Skybox::~Skybox()
	{
		glDeleteTextures(1, &_envCubemap);
	}

	void Skybox::Init() noexcept
	{
		// Create pass to cut hdr texture in 6
		QXuint captureRBO;

		glGenFramebuffers(1, &_captureFBO);
		glGenRenderbuffers(1, &captureRBO);

		glBindFramebuffer(GL_FRAMEBUFFER, _captureFBO);
		glBindRenderbuffer(GL_RENDERBUFFER, captureRBO);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 1024, 1024);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, captureRBO);

		// Create cubemap texture
		glGenTextures(1, &_envCubemap);
		glBindTexture(GL_TEXTURE_CUBE_MAP, _envCubemap);
		for (QXuint i = 0; i < 6; ++i)
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 1024, 1024, 0, GL_RGB, GL_FLOAT, nullptr);

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Set sampler
		_program->Use();

		glUniform1ui(_program->GetLocation("skyboxTexture"), 0);
	}

	void Skybox::CaptureCubemap() noexcept
	{
		// Create specific projections and cam to take "screenshots" and create 6 textures
		Math::QXmat4 proj = Math::QXmat4::CreateProjectionMatrix(1024, 1024, 0.478f, 10, 90);

		Math::QXmat4 views[] = {
			Math::QXmat4::CreateLookAtMatrix({0, 0, 0}, {1, 0, 0}, {0, -1, 0}), //BACK
			Math::QXmat4::CreateLookAtMatrix({0, 0, 0}, {-1, 0, 0}, {0, -1, 0}),
			Math::QXmat4::CreateLookAtMatrix({0, 0, 0}, {0, 1, 0}, {0, 0, 1}),//TOP
			Math::QXmat4::CreateLookAtMatrix({0, 0, 0}, {0, -1, 0}, {0, 0, -1}),//BOTTOM
			Math::QXmat4::CreateLookAtMatrix({0, 0, 0}, {0, 0, 1}, {0, -1, 0}),
			Math::QXmat4::CreateLookAtMatrix({0, 0, 0}, {0, 0, -1}, {0, -1, 0}), //FRONT
		};

		_cubemapProgram->Use();
		glDisable(GL_CULL_FACE);
		glDepthFunc(GL_LEQUAL);

		glUniformMatrix4fv(_cubemapProgram->GetLocation("projection"), 1, false, proj.array);
		glUniform1ui(_cubemapProgram->GetLocation("skyboxTexture"), 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _skyboxTexture->GetId());

		glViewport(0, 0, 1024, 1024);
		glBindFramebuffer(GL_FRAMEBUFFER, _captureFBO);
		// Render with all views
		for (QXuint i = 0; i < 6; ++i)
		{
			glUniformMatrix4fv(_cubemapProgram->GetLocation("captureView"), 1, false, views[i].array);

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, _envCubemap, 0);

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			renderCube();
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glDeleteFramebuffers(1, &_captureFBO);
		_cubemapProgram->Unuse();
	}

	void Skybox::renderCube() noexcept
	{
		// Draw the cube
		glBindVertexArray(_model->GetVAO());

		glDrawElements(GL_TRIANGLES, (GLsizei)_model->GetIndices().size(), GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
	}

	void Skybox::Render(Platform::AppInfo& info, QXuint sceneTexture, QXuint otherTexture, QXuint FBO) noexcept
	{
		if (!_isCubemapReady)
		{
			if (_model->IsReady() && _skyboxTexture->IsReady())
			{
				CaptureCubemap();
				_isCubemapReady = true;
				glViewport(0, 0, info.width, info.height);
			}
			else
				return;
		}

		// Render skybox
		glDisable(GL_CULL_FACE);
		_program->Use();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, _envCubemap);

		renderCube();

		glEnable(GL_CULL_FACE);
	}
}