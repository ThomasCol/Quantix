#include "Core/Render/PostProcess/PostProcessEffect.h"

#include <glad/glad.h>

namespace Quantix::Core::Render::PostProcess
{
	PostProcessEffect::PostProcessEffect(Resources::ShaderProgram* program, Resources::Model* quadModel) noexcept :
		_program	{program},
		_model		{quadModel}
	{
		glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	}
}