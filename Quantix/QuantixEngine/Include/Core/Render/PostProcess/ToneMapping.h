#ifndef __TONEMAPPING_H__
#define __TONEMAPPING_H__

#include "PostProcessEffect.h"

namespace Quantix::Core::Render::PostProcess
{
	class ToneMapping : public PostProcessEffect
	{
	private:
		#pragma region Function

		/**
		 * @brief Init Process
		 * 
		 * @param info  App info
		 */
		void Init(Platform::AppInfo& info) noexcept;

		#pragma endregion

		#pragma region Attributes

		QXuint						_VAO;
		Math::QXmat4				_correctionMatrix;

		#pragma endregion

	public:
		#pragma region Constructors

		/**
		 * @brief Construct a new Tone Mapping object
		 * 
		 * @param toneMappingProg Program for tone mappings
		 * @param model Model to render
		 * @param info App info
		 */
		ToneMapping(Resources::ShaderProgram* toneMappingProg, Resources::Model* model, Platform::AppInfo& info) noexcept;

		/**
		 * @brief Destroy the Tone Mapping object
		 * 
		 */
		~ToneMapping() = default;

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

