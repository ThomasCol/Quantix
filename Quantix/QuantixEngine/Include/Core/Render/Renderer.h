#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <glad/glad.h>

#include "Core/DLLHeader.h"
#include "Core/Type.h"
#include "Core/Components/Mesh.h"
#include "Core/Components/Light.h"

namespace Quantix::Core::Render
{
    class QUANTIX_API Renderer
    {
	private:
#pragma region Attributes

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
		void Draw(std::vector<Core::Components::Mesh*>& meshes, std::vector<Core::Components::Light*>& lights, Quantix::Core::Platform::AppInfo& info);

#pragma endregion
	};
}

#endif // __RENDERER_H__
