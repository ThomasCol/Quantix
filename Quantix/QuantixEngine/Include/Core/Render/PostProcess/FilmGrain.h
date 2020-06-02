#ifndef __FILMGRAIN_H__
#define __FILMGRAIN_H__

#include "PostProcessEffect.h"

namespace Quantix::Core::Render::PostProcess
{
	class FilmGrain : public PostProcessEffect
	{
	private:
		#pragma region Attributes

		QXuint						_VAO;

		QXfloat						_counterFilmGrain { 0.0f };
		QXfloat						_percentFilmGrain { 0.15f };

		#pragma endregion

	public:
		#pragma region Constructors

		/**
		 * @brief Construct a new Film Grain object
		 * 
		 * @param filmGrainProg Program for film grain
		 * @param model Model to render
		 * @param info App info
		 */
		FilmGrain(Resources::ShaderProgram* filmGrainProg, Resources::Model* model, Platform::AppInfo& info) noexcept;

		/**
		 * @brief Destroy the Film Grain object
		 * 
		 */
		~FilmGrain() = default;

		#pragma endregion

		#pragma region Functions

		/**
		 * @brief Render effect on screen
		 * 
		 * @param info App info
		 * @param sceneTexture Texture of the scene
		 * @param otherTexture Unused
		 * @param FBO FBO to use
		 */
		void Render(Platform::AppInfo& info, QXuint sceneTexture, QXuint otherTexture, QXuint FBO) noexcept override;

		#pragma endregion

		CLASS_REGISTRATION(Quantix::Core::Render::PostProcess::PostProcessEffect)
	};
}

#endif

