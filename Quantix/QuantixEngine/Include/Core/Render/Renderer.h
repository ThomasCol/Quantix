#ifndef __RENDERER_H__
#define __RENDERER_H__


#include "Core/Type.h"
#include "Core/Components/Mesh.h"
#include "Core/Components/Light.h"
#include "../../../QuantixEditor/include/Window.h"
#include "PostProcess/PostProcessEffect.h"

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

		struct Framebuffer
		{
			QXuint FBO = 0;
			QXuint texture = 0;
			QXuint depthStencilRenderbuffer = 0;
		};

		Framebuffer	_mainBuffer;

		QXuint		_viewProjMatrixUBO = 0;
		QXuint		_lightUBO = 0;

		PostProcess::PostProcessEffect* _effects;

		#pragma endregion

		#pragma region Functions

		/**
		 * @brief Create a Frame Buffer object
		 * 
		 * @param width Width of the window
		 * @param height Height of the window
		 */
		void CreateFrameBuffer(QXuint width, QXuint height) noexcept;

		/**
		 * @brief Create post process effects
		 * 
		 * @param manager ressource manager to create post process data
		 */
		void InitPostProcessEffects(DataStructure::ResourcesManager& manager) noexcept;

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
		 * @param width Window width
		 * @param height Window width
		 * @param resizeCallback Window callback for resize
		 * @param manager resources manager to instanciate datas
		 */
		Renderer(QXuint width, QXuint height, std::function<void(QXuint, QXuint)>& resizeCallback, DataStructure::ResourcesManager& manager) noexcept;

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
		 * @brief 
		 * 
		 * @param meshes Meshes to render
		 * @param lights Lights for the scene
		 * @param info App info
		 * @param cam Current camera for rendering
		 */
		QXuint Draw(std::vector<Core::Components::Mesh*>& meshes, std::vector<Core::Components::Light>& lights, Quantix::Core::Platform::AppInfo& info, Components::Camera* cam) noexcept;

		#pragma endregion
	};
}

#endif // __RENDERER_H__
