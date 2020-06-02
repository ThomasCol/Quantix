#include "Core/Render/PostProcess/Crosshair.h"

#include <glad/glad.h>

namespace Quantix::Core::Render::PostProcess
{
	Crosshair::Crosshair(Resources::ShaderProgram* crosshairProgram, Platform::AppInfo& info, Resources::Texture* texture):
		PostProcessEffect(crosshairProgram, nullptr),
		_crosshairTex { texture }
	{
        name = "Crosshair";
        enable = true;
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

        _program->Use();
        glUniform1i(_program->GetLocation("crosshairTex"), 0);
	}

	void Crosshair::Render(Platform::AppInfo& info, QXuint sceneTexture, QXuint otherTexture, QXuint FBO) noexcept
	{
        if (!_crosshairTex->IsReady())
            return;

        glDisable(GL_DEPTH_TEST);
        glBindFramebuffer(GL_FRAMEBUFFER, FBO);
        glClear(GL_DEPTH_BUFFER_BIT);

        _program->Use();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _crosshairTex->GetId());

        glBindVertexArray(_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glEnable(GL_DEPTH_TEST);
	}
}
