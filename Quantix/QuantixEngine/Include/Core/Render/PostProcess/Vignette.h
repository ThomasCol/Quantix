#ifndef __VIGNETTE_H__
#define __VIGNETTE_H__

#include "PostProcessEffect.h"

namespace Quantix::Core::Render::PostProcess
{
	class Vignette : public PostProcessEffect
	{
	private:
		#pragma region Attributes

		QXuint						_VAO;
		QXfloat						_outerRadius{ 0.7f };
		QXfloat						_innerRadius{ 0.3f };

		#pragma endregion

	public:
		#pragma region Constructors

		/**
		 * @brief Construct a new Vignette object
		 * 
		 * @param vignetteProg Vignette program
		 * @param model Model to render
		 * @param info App info
		 */
		Vignette(Resources::ShaderProgram* vignetteProg, Resources::Model* model, Platform::AppInfo& info) noexcept;

		/**
		 * @brief Destroy the Vignette object
		 * 
		 */
		~Vignette() = default;

		#pragma endregion

		#pragma region Functions

		/**
		 * @brief Render effect on screen
		 * 
		 * @param info App info
		 * @param sceneTexture Scene for the texture
		 * @param otherTexture Unused
		 * @param FBO FBO to use
		 */
		void Render(Platform::AppInfo& info, QXuint sceneTexture, QXuint otherTexture, QXuint FBO) noexcept override;

		#pragma endregion

		CLASS_REGISTRATION(Quantix::Core::Render::PostProcess::PostProcessEffect)
	};
}

#endif


