#ifndef __RENDERER_H__
#define __RENDERER_H__


#include "Core/Type.h"
#include "Core/Components/Mesh.h"
#include "Core/Components/Light.h"
#include "../../../QuantixEditor/include/Window.h"

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

#pragma endregion

#pragma region Functions

		void CreateFrameBuffer(QXuint width, QXuint height);

#pragma endregion

	public:
#pragma region Constructors
		/**
		 * @brief Construct a new Renderer object
		 * 
		 * @param width Window width
		 * @param height Window width
		 * @param resizeCallback Window callback for resize
		 */
		Renderer(QXuint width, QXuint height, std::function<void(QXuint, QXuint)>& resizeCallback);

		/**
		 * @brief Destroy the Renderer object
		 */
		~Renderer() = default;

#pragma endregion

#pragma region Functions
		/**
		 * @brief 
		 * 
		 * @param meshes Meshes to render
		 * @param lights Lights for the scene
		 * @param info App info
		 */
		QXuint Draw(std::vector<Core::Components::Mesh*>& meshes, std::vector<Core::Components::Light*>& lights, Quantix::Core::Platform::AppInfo& info);

#pragma endregion
	};
}

#endif // __RENDERER_H__
