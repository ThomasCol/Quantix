#ifndef __CROSSHAIR_H__
#define __CROSSHAIR_H__

#include "PostProcessEffect.h"
#include "Resources/Texture.h"

namespace Quantix::Core::Render::PostProcess
{
	class Crosshair : public PostProcessEffect
	{
	private:
		#pragma region Attributes

		Resources::Texture*			_crosshairTex;

		QXuint						_VAO;

		#pragma endregion

	public:
		#pragma region Constructors
		
		/**
		 * @brief Construct a new Crosshair object
		 * 
		 * @param crosshairProgram Program for crosshair
		 * @param info App info
		 * @param texture Texture of the crosshair
		 */
		Crosshair(Resources::ShaderProgram* crosshairProgram, Platform::AppInfo& info, Resources::Texture* texture) noexcept;

		/**
		 * @brief Destroy the Crosshair object
		 */
		~Crosshair() = default;

		#pragma endregion

		#pragma region Functions

		/**
		 * @brief Render effect on screen
		 * 
		 * @param info App info
		 * @param sceneTexture Texture of the scene
		 * @param otherTexture unuse
		 * @param FBO FBO tu use
		 */
		void	Render(Platform::AppInfo & info, QXuint sceneTexture, QXuint otherTexture, QXuint FBO) noexcept override;

		#pragma endregion

		CLASS_REGISTRATION(Quantix::Core::Render::PostProcess::PostProcessEffect)
	};
}

#endif // !__CROSSHAIR_H__