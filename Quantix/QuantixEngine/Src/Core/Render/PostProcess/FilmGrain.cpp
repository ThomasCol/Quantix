#include "Core/Render/PostProcess/FilmGrain.h"
#include <glad/glad.h>

RTTR_PLUGIN_REGISTRATION
{
    rttr::registration::class_<Quantix::Core::Render::PostProcess::FilmGrain>("FilmGrain")
    .property("Percent", &Quantix::Core::Render::PostProcess::FilmGrain::_percentFilmGrain);
}

namespace Quantix::Core::Render::PostProcess
{
	FilmGrain::FilmGrain(Resources::ShaderProgram* toneMappingProg, Resources::Model* model, Platform::AppInfo& info) noexcept :
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

        _counterFilmGrain += 0.01;
        if (_counterFilmGrain > 100.f)
            _counterFilmGrain = 0.f;

        glUniform1f(_program->GetLocation("uAmount"), _counterFilmGrain);
        glUniform1f(_program->GetLocation("uCoef"), _percentFilmGrain);

        glBindTexture(GL_TEXTURE_2D, sceneTexture);
        glBindVertexArray(_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
}