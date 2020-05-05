#ifndef __BLOOM_H__
#define __BLOOM_H__

#include "PostProcessEffect.h"

namespace Quantix::Core::Render::PostProcess
{
	class Bloom : public PostProcessEffect
	{
	private:
		#pragma region Attributes

		Resources::ShaderProgram*	_bloomProgram;

		BlurFramebuffer				_blurBuffer;
		Framebuffer					_bloomBuffer;

		QXuint						_VAO;

		#pragma endregion

		#pragma region Functions

		/**
		 * @brief Init buffers for the bloom
		 * 
		 * @param info app info
		 */
		void Init(Platform::AppInfo& info) noexcept;

		#pragma endregion

	public:
		#pragma region Constructors

		/**
		 * @brief Construct a new Bloom object
		 * 
		 * @param blurProgram shader program for blur
		 * @param bloomProgram shader program for bloom
		 * @param model model to use
		 * @param info app info
		 */
		Bloom(Resources::ShaderProgram* blurProgram, Resources::ShaderProgram* bloomProgram, Resources::Model* model, Platform::AppInfo& info);

		/**
		 * @brief Destroy the Bloom object
		 * 
		 */
		~Bloom() = default;

		#pragma endregion

		#pragma region Functions

		
		void Render(Platform::AppInfo& info, QXuint sceneTexture, QXuint otherTexture, QXuint FBO) noexcept override;

		#pragma endregion
	};
}

#endif // !__BLOOM_H__
