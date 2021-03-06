#include "Core/Render/PostProcess/Vignette.h"
#include <glad/glad.h>

RTTR_PLUGIN_REGISTRATION
{
    rttr::registration::class_<Quantix::Core::Render::PostProcess::Vignette>("Vignette")
    .property("OuterRadius", &Quantix::Core::Render::PostProcess::Vignette::_outerRadius)
    .property("InnerRadius", &Quantix::Core::Render::PostProcess::Vignette::_innerRadius);
}

namespace Quantix::Core::Render::PostProcess
{

    Vignette::Vignette(Resources::ShaderProgram* toneMappingProg, Resources::Model* model, Platform::AppInfo& info) noexcept :
        PostProcessEffect(toneMappingProg, model)
    {
        name = "Vignette";
        
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

    void Vignette::Render(Platform::AppInfo& info, QXuint sceneTexture, QXuint otherTexture, QXuint FBO) noexcept
    {
        glBindFramebuffer(GL_FRAMEBUFFER, FBO);

        _program->Use();

        glUniform2f(_program->GetLocation("uResolution"), info.width, info.height);

        glUniform1f(_program->GetLocation("uOuterRadius"), _outerRadius);
        glUniform1f(_program->GetLocation("uInnerRadius"), _innerRadius);
        
        glBindTexture(GL_TEXTURE_2D, sceneTexture);
        glBindVertexArray(_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
}