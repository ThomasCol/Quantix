#ifndef __FILMGRAIN_H__
#define __FILMGRAIN_H__

#include "PostProcessEffect.h"

namespace Quantix::Core::Render::PostProcess
{
	class FilmGrain : public PostProcessEffect
	{
	private:
		QXuint						_VAO;

		QXfloat						_counterFilmGrain { 0.0f };
		QXfloat						_percentFilmGrain { 0.15f };
	public:
		FilmGrain(Resources::ShaderProgram* toneMappingProg, Resources::Model* model, Platform::AppInfo& info);
		~FilmGrain() = default;

		void Render(Platform::AppInfo& info, QXuint sceneTexture, QXuint otherTexture, QXuint FBO) noexcept override;

		CLASS_REGISTRATION(Quantix::Core::Render::PostProcess::PostProcessEffect)
	};
}

#endif

