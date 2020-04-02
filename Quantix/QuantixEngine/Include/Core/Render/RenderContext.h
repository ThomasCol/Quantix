#ifndef __RENDERCONTEXT_H__
#define __RENDERCONTEXT_H__

#include <GLFW/glfw3.h>
#include <vector>

#include "CommandPool.h"

namespace Quantix::Core::Render
{
	class RenderContext
	{
	private:
#pragma region Attributes

		const std::vector<const char*> _validationLayers{
				"VK_LAYER_KHRONOS_validation",
		};

		const std::vector<const char*> _deviceExtensions{
				VK_KHR_SWAPCHAIN_EXTENSION_NAME
		};

		VkDebugUtilsMessengerEXT		_debugMessenger;

#ifdef NDEBUG
		const bool enableValidationLayers = false;
#else
		const bool enableValidationLayers = true;
#endif

#pragma endregion

#pragma region Functions

		void CreateInstance();
		bool CheckValidationLayerSupport();
		std::vector<const char*> GetRequiredEtensions();
		void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
		void CheckExtension();
		void SetupDebugMessenger();

		VkResult CreateDebugUtilsMessengerEXT(VkInstance instance,
			const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
			const VkAllocationCallbacks* pAllocator,
			VkDebugUtilsMessengerEXT* pDebugMessenger);

		void DestroyDebugUtilsMessengerEXT(VkInstance instance,
			VkDebugUtilsMessengerEXT debugMessenger,
			const VkAllocationCallbacks* pAllocator);

		void	CreateLogicalDevice();
		void	PickPhysicalDevice();
		int		RateDeviceSuitability(VkPhysicalDevice device);
		void	CreateSurface(GLFWwindow* window);
		void	CreateCommandPool();

#pragma endregion

	public:

#pragma region Attributes

		VkInstance			instance;
		VkDevice			device;
		VkPhysicalDevice	physicalDevice{ VK_NULL_HANDLE };
		CommandPool			commandPool;
		VkQueue				graphicsQueue;
		VkQueue 			presentQueue;
		VkSurfaceKHR 		surface;

#pragma endregion

#pragma region Constructors

		RenderContext(GLFWwindow* window);
		~RenderContext();

#pragma endregion

#pragma region Functions

		static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
			VkDebugUtilsMessageTypeFlagsEXT messageType,
			const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
			void* pUserData);

#pragma endregion
	};
}

#endif // __RENDERCONTEXT_H__
