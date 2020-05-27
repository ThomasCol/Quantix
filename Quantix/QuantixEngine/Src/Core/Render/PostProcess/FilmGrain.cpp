#include "Core/Render/PostProcess/FilmGrain.h"
#include <glad/glad.h>

namespace Quantix::Core::Render::PostProcess
{
	FilmGrain::FilmGrain(Resources::ShaderProgram* toneMappingProg, Resources::Model* model, Platform::AppInfo& info) :
		PostProcessEffect(toneMappingProg, model)
	{
        name = "FilmGrain";

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

    void FilmGrain::Render(Platform::AppInfo& info, QXuint sceneTexture, QXuint otherTexture, QXuint FBO) noexcept
    {
        glBindFramebuffer(GL_FRAMEBUFFER, FBO);

        _program->Use();

        glUniform1f(_program->GetLocation("uAmount"), counterFilmGrain);
        glUniform1f(_program->GetLocation("uCoef"), percentFilmGrain);

        glBindTexture(GL_TEXTURE_2D, sceneTexture);
        glBindVertexArray(_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
}