#include "Core/Render/PostProcess/Bloom.h"

#include <glad/glad.h>
#include "Core/Debugger/Logger.h"

#define OFFSETOF(TYPE, MEMBER) __builtin_offsetof(TYPE, MEMBER)

struct quad_vertex
{
    Math::QXvec2 Position;
    Math::QXvec2 UV;
};

namespace Quantix::Core::Render::PostProcess
{
	Bloom::Bloom(Resources::ShaderProgram* blurProgram, Resources::ShaderProgram* bloomProgram, Resources::Model* model, Platform::AppInfo& info) :
		PostProcessEffect(blurProgram, model),
		_bloomProgram {bloomProgram}
	{
        Init(info);

        QXuint VBO;
        // Gen unit quad
        {
            quad_vertex Quad[6] =
            {
                { {-1.f,-1.f }, { 0.f, 0.f } }, // bl
                { { 1.f,-1.f }, { 1.f, 0.f } }, // br
                { { 1.f, 1.f }, { 1.f, 1.f } }, // tr

                { {-1.f, 1.f }, { 0.f, 1.f } }, // tl
                { {-1.f,-1.f }, { 0.f, 0.f } }, // bl
                { { 1.f, 1.f }, { 1.f, 1.f } }, // tr
            };

            // Upload mesh to gpu
            glGenBuffers(1, &VBO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(quad_vertex), Quad, GL_STATIC_DRAW);
        }

        // Create a vertex array and bind it
        glGenVertexArrays(1, &_VAO);

        glBindVertexArray(_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(quad_vertex), (void*)OFFSETOF(quad_vertex, Position));
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(quad_vertex), (void*)OFFSETOF(quad_vertex, UV));
        glBindVertexArray(0);
	}

	void Bloom::Init(Platform::AppInfo& info) noexcept
	{
        QXuint FBO[2];
        glGenFramebuffers(2, FBO);

        GLuint ColorTexture[2];
        glGenTextures(2, ColorTexture);
        for (int i = 0; i < 2; ++i)
        {
            glBindFramebuffer(GL_FRAMEBUFFER, FBO[i]);
            glBindTexture(GL_TEXTURE_2D, ColorTexture[i]);
            glTexImage2D(
                GL_TEXTURE_2D, 0, GL_RGB16F, info.width, info.height, 0, GL_RGB, GL_FLOAT, NULL
            );
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glFramebufferTexture2D(
                GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ColorTexture[i], 0
            );
            _blurBuffer.FBO[i] = FBO[i];
            _blurBuffer.texture[i] = ColorTexture[i];
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        QXint previous_framebuffer;
        glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &previous_framebuffer);

        // Create Framebuffer that will hold 1 color attachement
        QXuint FBO2;
        glGenFramebuffers(1, &FBO2);
        glBindFramebuffer(GL_FRAMEBUFFER, FBO2);

        // Create texture that will be used as color attachment
        QXuint texture;
        glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, info.width, info.height, 0, GL_RGBA, GL_FLOAT, nullptr);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

        GLuint depth_stencil_renderbuffer;
        glGenRenderbuffers(1, &depth_stencil_renderbuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, depth_stencil_renderbuffer);
        glObjectLabel(GL_RENDERBUFFER, depth_stencil_renderbuffer, -1, "DepthStencilRenderbuffer");
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, info.width, info.height);

        // Setup attachements
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth_stencil_renderbuffer);

        QXuint draw_attachments = { GL_COLOR_ATTACHMENT0 };
        glDrawBuffers(1, &draw_attachments);

        GLenum framebuffer_status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (framebuffer_status != GL_FRAMEBUFFER_COMPLETE)
        {
            LOG(ERROR, std::string("framebuffer failed to complete (0x%x)\n", framebuffer_status));
        }

        glBindFramebuffer(GL_FRAMEBUFFER, previous_framebuffer);

        _bloomBuffer.FBO = FBO2;
        _bloomBuffer.texture = texture;
        _bloomBuffer.depthBuffer = depth_stencil_renderbuffer;
	}

    void Bloom::Render(Platform::AppInfo& info, QXuint sceneTexture, QXuint otherTexture, QXuint FBO) noexcept
    {
        glDisable(GL_DEPTH_TEST);
        QXbool horizontal = true, first_iteration = true;

        QXfloat weight[] = { 0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216 };


        // Apply two-pass gaussian blur on Bright render FBO
        _program->Use();
        glUniform1i(glGetUniformLocation(_program->GetID(), "image"), 0);
        glActiveTexture(GL_TEXTURE0);
        for (unsigned int i = 0; i < 50; i++)
        {
            glBindFramebuffer(GL_FRAMEBUFFER, _blurBuffer.FBO[horizontal]);
            glUniform1i(glGetUniformLocation(_program->GetID(), "horizontal"), horizontal);
            for (int i = 0; i < 5; ++i)
            {
                glUniform1f(glGetUniformLocation(_program->GetID(), (std::string("weight[") + std::to_string(i) + "]").c_str()), weight[i]);
            }
            glBindTexture(GL_TEXTURE_2D, first_iteration ? otherTexture : _blurBuffer.texture[!horizontal]);  // bind texture of other framebuffer (or scene if first iteration)
            glBindVertexArray(_VAO);

            glDrawArrays(GL_TRIANGLES, 0, 6);

            glBindVertexArray(0);

            horizontal = !horizontal;
            if (first_iteration)
                first_iteration = false;
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // Apply final bloom
        {
            glBindFramebuffer(GL_FRAMEBUFFER, FBO);
            glClear(GL_DEPTH_BUFFER_BIT);

            _bloomProgram->Use();
            // Bind base scene texture and blured texture
            glUniform1i(glGetUniformLocation(_bloomProgram->GetID(), "scene"), 0);
            glUniform1i(glGetUniformLocation(_bloomProgram->GetID(), "bloomBlur"), 1);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, sceneTexture);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, _blurBuffer.texture[!horizontal]);

            glUniform1i(glGetUniformLocation(_bloomProgram->GetID(), "bloom"), true);
            glUniform1f(glGetUniformLocation(_bloomProgram->GetID(), "exposure"), 0.5);
            glUniform1f(glGetUniformLocation(_bloomProgram->GetID(), "gamma"), 1.7);

            glBindVertexArray(_VAO);

            glDrawArrays(GL_TRIANGLES, 0, 6);

            glBindVertexArray(0);
            glBindTexture(GL_TEXTURE_2D, 0);
            glActiveTexture(GL_TEXTURE0);
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }
    }
}