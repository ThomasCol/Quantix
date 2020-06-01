#include "Core/Render/PostProcess/PostProcessEffect.h"

#include <glad/glad.h>

RTTR_PLUGIN_REGISTRATION
{
	rttr::registration::class_<Quantix::Core::Render::PostProcess::PostProcessEffect>("PostProcessEffect")
	.property("Enable", &Quantix::Core::Render::PostProcess::PostProcessEffect::enable)
	.property("Name", &Quantix::Core::Render::PostProcess::PostProcessEffect::name);
}

namespace Quantix::Core::Render::PostProcess
{
	PostProcessEffect::PostProcessEffect(Resources::ShaderProgram* program, Resources::Model* quadModel) noexcept :
		_program	{program},
		_model		{quadModel}
	{
		glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	}
}