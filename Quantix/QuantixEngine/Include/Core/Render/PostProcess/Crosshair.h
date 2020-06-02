#ifndef __CROSSHAIR_H__
#define __CROSSHAIR_H__

#include "PostProcessEffect.h"
#include "Resources/Texture.h"

namespace Quantix::Core::Render::PostProcess
{
	class Crosshair : public PostProcessEffect
	{
	private:
		Resources::Texture*			_crosshairTex;

		QXuint						_VAO;

	public:
		Crosshair(Resources::ShaderProgram* crosshairProgram, Platform::AppInfo& info, Resources::Texture* texture);
		~Crosshair() = default;

		void Render(Platform::AppInfo & info, QXuint sceneTexture, QXuint otherTexture, QXuint FBO) noexcept override;

		CLASS_REGISTRATION(Quantix::Core::Render::PostProcess::PostProcessEffect)
	};
}

#endif // !__CROSSHAIR_H__