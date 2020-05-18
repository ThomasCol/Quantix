#ifndef __RENDERER_H__
#define __RENDERER_H__


#include <Type.h>
#include "Core/Components/Mesh.h"
#include "Core/Components/Light.h"
#include "../../../QuantixEditor/include/Window.h"
#include "Core/Components/Collider.h"
#include "PostProcess/Bloom.h"

namespace Quantix::Core::DataStructure
{
	class ResourcesManager;
}

namespace Quantix::Core::Render
{
    class QUANTIX_API Renderer
    {
	private:
		#pragma region Attributes

		RenderFramebuffer				_mainBuffer;
		RenderFramebuffer				_gameBuffer;

		Framebuffer 					_shadowBuffer;
		Framebuffer 					_finalGameBuffer;
		Framebuffer 					_finalSceneBuffer;

		QXuint							_viewProjMatrixUBO = 0;
		QXuint							_viewProjShadowMatrixUBO = 0;
		QXuint							_lightUBO = 0;

		Math::QXmat4 					_projLight;

		PostProcess::PostProcessEffect*	_effects;
		PostProcess::Bloom* 			_bloom;

		Resources::ShaderProgram* 		_wireFrameProgram;
		Resources::ShaderProgram* 		_shadowProgram;

		Resources::Model* 				_cube;
		Resources::Model* 				_sphere;
		Resources::Model* 				_caps;

		#pragma endregion

		#pragma region Functions

		/**
		 * @brief Create a Framebuffer object
		 * 
		 * @param width Width of the window
		 * @param height Height of the window
		 * @param fbo fbo to initialize
		 */
		void CreateFramebuffer(QXuint width, QXuint height, Framebuffer& fbo) noexcept;

		/**
		 * @brief Init the shadow buffer
		 * 
		 */
		void InitShadowBuffer() noexcept;


		/**
		 * @brief Create post process effects
		 * 
		 * @param manager ressource manager to create post process data
		 */
		void InitPostProcessEffects(DataStructure::ResourcesManager& manager, Platform::AppInfo& info) noexcept;

		/**
		 * @brief Draw the shadow pass
		 * 
		 * @param meshes meshes to use
		 * @param info app info
		 * @param lights ligths to use
		 */
		void RenderShadows(std::vector<Core::Components::Mesh*> & meshes, Quantix::Core::Platform::AppInfo & info,
			std::vector<Core::Components::Light> & lights);

		void RenderColliders(std::vector<Components::ICollider*>& colliders);

		void SendUniformBuffer(std::vector<Core::Components::Light>& lights, Core::Platform::AppInfo& info, Components::Camera* cam);

		#pragma endregion

	public:
		#pragma region Constructors

		/**
		 * @brief Construct a new Renderer object (DELETED)
		 */
		Renderer() = delete;

		/**
		 * @brief Construct a new Renderer object (DELETED)
		 * 
		 * @param renderer renderer to copy
		 */
		Renderer(const Renderer& renderer) = delete;

		/**
		 * @brief Construct a new Renderer object (DELETED)
		 * 
		 * @param renderer renderer to move
		 */
		Renderer(Renderer&& renderer) = delete;

		/**
		 * @brief Construct a new Renderer object
		 * 
		 * @param info App info
		 * @param manager Resources manager
		 */
		Renderer(Platform::AppInfo& info, DataStructure::ResourcesManager& manager) noexcept;

		/**
		 * @brief Destroy the Renderer object
		 */
		~Renderer() = default;

		#pragma endregion

		#pragma region Operators

		/**
		 * @brief Operator for copy (DELETED)
		 * 
		 * @param renderer renderer to copy
		 * @return Renderer& reference to the current renderer
		 */
		Renderer& operator=(const Renderer& renderer) = delete;

		/**
		 * @brief Operator for move (DELETED)
		 * 
		 * @param renderer renderer to move
		 * @return Renderer& reference to the current renderer
		 */
		Renderer& operator=(Renderer&& renderer) = delete;

		#pragma endregion

		#pragma region Functions

		/**
		 * @brief Create a Render Framebuffer object
		 *
		 * @param width Width of the window
		 * @param height Height of the window
		 * @param fbo fbo to initialize
		 */
		void CreateRenderFramebuffer(QXuint width, QXuint height, RenderFramebuffer & fbo) noexcept;

		/**
		 * @brief Function to draw current scene as a scene
		 * 
		 * @param meshes meshes to draw
		 * @param colliders colliders to draw
		 * @param lights lights to use
		 * @param info app info
		 * @param cam camera to use
		 * @return QXuint created texture
		 */
		QXuint Draw(std::vector<Core::Components::Mesh*>& meshes, std::vector<Components::ICollider*>& colliders, std::vector<Core::Components::Light>& lights,
				Quantix::Core::Platform::AppInfo& info, Components::Camera* cam, RenderFramebuffer& buffer, bool displayColliders) noexcept;

		#pragma endregion
	};
}

#endif // __RENDERER_H__
