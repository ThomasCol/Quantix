#ifndef __SKYBOX_H__
#define __SKYBOX_H__

#include "PostProcessEffect.h"
#include "Resources/Texture.h"

namespace Quantix::Core::Render::PostProcess
{
	class Skybox : public PostProcessEffect
	{
	private:
#pragma region Attributes

		Resources::Texture* _skyboxTexture;
		Resources::ShaderProgram* _cubemapProgram;

		QXuint _captureFBO;
		QXuint _envCubemap;

		QXbool	_isCubemapReady = false;

#pragma endregion

#pragma region Functions

		/**
		 * @brief Init the data for the skybox rendering
		 * 
		 */
		void Init() noexcept;

		/**
		 * @brief Do the pass to change hdr texture to cubemap
		 * 
		 */
		void CaptureCubemap() noexcept;

		/**
		 * @brief Draw a cube
		 * 
		 */
		void renderCube() noexcept;

#pragma endregion

	public:
#pragma region Constructors

		/**
		 * @brief Construct a new Skybox object
		 */
		Skybox() = default;

		/**
		 * @brief Construct a new Skybox object
		 * 
		 * @param skybox skybox to copy
		 */
		Skybox(const Skybox& skybox) = default;

		/**
		 * @brief Construct a new Skybox object
		 * 
		 * @param skybox skybox to move
		 */
		Skybox(Skybox&& skybox) = default;

		/**
		 * @brief Construct a new Skybox object
		 * 
		 * @param cubemapShader Shader to create the cubemap
		 * @param backgroundProgram Shader to render the cubemap to make the skybox
		 * @param quadModel Model to use for rendering
		 * @param skyTexture texture to use for the skybox
		 */
		Skybox(Resources::ShaderProgram* cubemapShader, Resources::ShaderProgram* backgroundProgram, Resources::Model* model, Resources::Texture* skyTexture) noexcept;

		/**
		 * @brief Destroy the Skybox object
		 */
		~Skybox();

#pragma endregion

#pragma region Functions

		/**
		 * @brief Render the skybox
		 * 
		 * @param info info of the application
		 */
		void Render(Platform::AppInfo& info, QXuint sceneTexture, QXuint otherTexture, QXuint FBO) noexcept override;

#pragma endregion
	};
}

#endif __SKYBOX_H__
