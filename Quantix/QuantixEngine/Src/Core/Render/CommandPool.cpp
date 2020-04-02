#include "Core/Render/CommandPool.h"

#include <stdexcept>

namespace Quantix::Core::Render
{
	CommandPool& CommandPool::Create(VkDevice device, uint32_t familyQueueIndex, VkCommandPoolCreateFlags flags)
	{
		VkCommandPoolCreateInfo poolInfo = {};
		poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		poolInfo.queueFamilyIndex = familyQueueIndex;
		poolInfo.flags = flags;

		if (vkCreateCommandPool(device, &poolInfo, nullptr, &_commandPool) != VK_SUCCESS)
			throw std::runtime_error("failed to create command pool!");

		return *this;
	}

	CommandBuffer& CommandPool::AllocateCommandBuffer(VkDevice device, VkCommandBufferAllocateInfo* allocateInfo,
		VkCommandBuffer* commandBuffer)
	{
		allocateInfo->commandPool = _commandPool;
		if (vkAllocateCommandBuffers(device, allocateInfo, commandBuffer) != VK_SUCCESS)
			throw std::runtime_error("failed to allocate command buffers!");
	}

	void CommandPool::FreeCommandBuffer(VkDevice device, uint32_t bufferCount, VkCommandBuffer* commandBuffer)
	{
		vkFreeCommandBuffers(device, _commandPool, bufferCount, commandBuffer);
	}

	void CommandPool::Destroy(VkDevice device)
	{
		vkDestroyCommandPool(device, _commandPool, nullptr);
	}
}