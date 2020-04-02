#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <functional>

#include "Core/Type.h"
#include "Core/Components/Mesh.h"
#include "Core/Components/Light.h"
#include "RenderContext.h"

namespace Quantix::Core::Render
{
    class QUANTIX_API Renderer
    {
	private:
#pragma region Attributes

		RenderContext					_context;
		VkSwapchainKHR					_swapChain;
		std::vector<VkImage>			_swapChainImages;
		VkFormat						_swapChainImageFormat;
		VkExtent2D						_swapChainExtent;
		std::vector<VkImageView>		_swapChainImageViews;

		struct SwapChainSupportDetails
		{
			VkSurfaceCapabilitiesKHR capabilities;
			std::vector<VkSurfaceFormatKHR> formats;
			std::vector<VkPresentModeKHR> presentModes;
		};

#pragma endregion

#pragma region Functions

		void					CreateSwapChain(GLFWwindow* window);
		SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);
		VkSurfaceFormatKHR		ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		VkPresentModeKHR		ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
		VkExtent2D				ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, GLFWwindow* window);

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
		Renderer(QXuint width, QXuint height, std::function<void(QXuint, QXuint)>& resizeCallback, GLFWwindow* window);

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
