#ifndef __VIGNETTE_H__
#define __VIGNETTE_H__

#include "PostProcessEffect.h"

namespace Quantix::Core::Render::PostProcess
{
	class Vignette : public PostProcessEffect
	{
	private:
		// Vignette
		QXuint						_VAO;
		QXfloat OuterRadius{ 0.7f };
		QXfloat InnerRadius{ 0.3f };
	public:
		Vignette(Resources::ShaderProgram* toneMappingProg, Resources::Model* model, Platform::AppInfo& info);
		~Vignette() = default;

		void Render(Platform::AppInfo& info, QXuint sceneTexture, QXuint otherTexture, QXuint FBO) noexcept override;
	};
}

#endif


