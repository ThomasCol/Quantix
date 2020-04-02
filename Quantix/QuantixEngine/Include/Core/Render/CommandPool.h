#pragma once

#include <Vulkan/vulkan.h>
#include "CommandBuffer.h"

namespace Quantix::Core::Render
{
	class CommandPool
	{
	public:
		CommandPool() = default;
		~CommandPool() = default;

		CommandPool& Create(VkDevice device, uint32_t familyQueueIndex, VkCommandPoolCreateFlags flags);

		CommandBuffer& AllocateCommandBuffer(VkDevice device, VkCommandBufferAllocateInfo* info, VkCommandBuffer* commandBuffer);
		void FreeCommandBuffer(VkDevice device, uint32_t bufferCount, VkCommandBuffer* commandBuffer);

		void Destroy(VkDevice device);

	private:
		VkCommandPool					_commandPool;
		uint32_t						_familyQueue;
	};
}