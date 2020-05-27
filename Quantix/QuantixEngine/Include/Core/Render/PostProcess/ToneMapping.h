#ifndef __TONEMAPPING_H__
#define __TONEMAPPING_H__

#include "PostProcessEffect.h"

namespace Quantix::Core::Render::PostProcess
{
	class ToneMapping : public PostProcessEffect
	{
	private:

		void Init(Platform::AppInfo& info) noexcept;

		QXuint						_VAO;
		Math::QXmat4				correctionMatrix;
	public:
		ToneMapping(Resources::ShaderProgram* toneMappingProg, Resources::Model* model, Platform::AppInfo& info);
		~ToneMapping() = default;

		void Render(Platform::AppInfo& info, QXuint sceneTexture, QXuint otherTexture, QXuint FBO) noexcept override;
	};
}

#endif

