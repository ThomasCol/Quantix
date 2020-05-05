#ifndef __BLOOM_H__
#define __BLOOM_H__

#include "PostProcessEffect.h"

namespace Quantix::Core::Render::PostProcess
{
	class Bloom : public PostProcessEffect
	{
	private:
		Resources::ShaderProgram* _bloomProgram;

		struct BlurFramebuffer
		{
			QXuint FBO[2];
			QXuint texture[2];
		};

		struct BloomFramebuffer
		{
			QXuint FBO = 0;
			QXuint texture = 0;
			QXuint depthBuffer = 0;
		};

		BlurFramebuffer _blurBuffer;
		BloomFramebuffer _bloomBuffer;

		void Init(Platform::AppInfo& info) noexcept;

	public:
		Bloom(Resources::ShaderProgram* blurProgram, Resources::ShaderProgram* bloomProgram, Resources::Model* model, Platform::AppInfo& info);
		~Bloom() = default;

		void Render(Platform::AppInfo& info, QXuint sceneTexture, QXuint otherTexture, QXuint FBO) noexcept override;


	};
}

#endif // !__BLOOM_H__
