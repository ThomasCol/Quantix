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

		QXuint						_amout { 11 };

		QXfloat						_weight[5] { 0.260f, 0.195f, 0.122f, 0.074f, 0.20f };

		QXbool						_hdrOnly { false };

		QXfloat						_exposure { 1.340f };
		QXfloat						_gamma { 0.320f };

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
		Bloom(Resources::ShaderProgram* blurProgram, Resources::ShaderProgram* bloomProgram, Resources::Model* model, Platform::AppInfo& info) noexcept;

		/**
		 * @brief Destroy the Bloom object
		 * 
		 */
		~Bloom() = default;

		#pragma endregion

		#pragma region Functions

		/**
		 * @brief Render effect on screen
		 * 
		 * @param info App info
		 * @param sceneTexture Texture for the scene
		 * @param otherTexture Bright only texture
		 * @param FBO FBO tu use
		 */
		void Render(Platform::AppInfo& info, QXuint sceneTexture, QXuint otherTexture, QXuint FBO) noexcept override;

		#pragma endregion

		CLASS_REGISTRATION(Quantix::Core::Render::PostProcess::PostProcessEffect)
	};
}

#endif // !__BLOOM_H__
