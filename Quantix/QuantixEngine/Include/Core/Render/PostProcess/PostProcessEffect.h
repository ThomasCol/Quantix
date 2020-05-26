#ifndef __POSTPROCESSEFFECT_H__
#define __POSTPROCESSEFFECT_H__

#include "Resources/ShaderProgram.h"
#include "Resources/Model.h"
#include "Core/Platform/Appinfo.h"
#include "Core/Render/Framebuffers.h"

namespace Quantix::Core::Render::PostProcess
{
	class PostProcessEffect
	{
	protected:
		#pragma region Attributes

		Resources::ShaderProgram*	_program;
		Resources::Model*			_model;

		#pragma endregion

	public:
		#pragma region Constructors

		/**
		 * @brief Construct a new Post Process Effect object
		 */
		PostProcessEffect() = default;

		/**
		 * @brief Construct a new Post Process Effect object
		 * 
		 * @param postProcess process to copy
		 */
		PostProcessEffect(const PostProcessEffect& postProcess) = default;

		/**
		 * @brief Construct a new Post Process Effect object
		 * 
		 * @param postProcess process to move
		 */
		PostProcessEffect(PostProcessEffect&& postProcess) = default;

		/**
		 * @brief Construct a new Post Process Effect object
		 * 
		 * @param program program for the process
		 * @param model model to use for the process
		 */
		PostProcessEffect(Resources::ShaderProgram* program, Resources::Model* model) noexcept;

		/**
		 * @brief Destroy the Post Process Effect object
		 */
		virtual ~PostProcessEffect() = default;

		#pragma endregion

		#pragma region Operator

		/**
		 * @brief Operator for copy
		 * 
		 * @param effect post process effect to copy
		 * @return PostProcessEffect& reference to the current post process effect
		 */
		PostProcessEffect& operator=(const PostProcessEffect& effect) = default;

		/**
		 * @brief Operator for move
		 * 
		 * @param effect post process effect to move
		 * @return PostProcessEffect& reference to the current post process effect
		 */
		PostProcessEffect& operator=(PostProcessEffect&& effect) = default;

		#pragma endregion

		#pragma region Function

		/**
		 * @brief Render the post process effect
		 * 
		 * @param info app info
		 * @param sceneTexture current texture of the scene
		 * @param otherTexture additionnal texture if needed
		 * @param FBO FBO to use to render
		 */
		virtual void Render(Platform::AppInfo& info, QXuint sceneTexture, QXuint otherTexture, QXuint FBO) noexcept = 0;

		#pragma endregion

		#pragma region Attributes

		QXstring	name = "";

		QXbool		enable = true;

		#pragma endregion
	};
}

#endif
