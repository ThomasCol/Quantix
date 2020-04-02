#include "Core/Render/CommandBuffer.h"

#include "Core/Render/RenderContext.h"

namespace Quantix::Core::Render
{
	CommandBuffer& CommandBuffer::BeginOneTime(RenderContext& context)
	{
		VkCommandBufferAllocateInfo allocInfo = {};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandBufferCount = 1;

		context.commandPool.AllocateCommandBuffer(context.device, &allocInfo, &_buffer);

		VkCommandBufferBeginInfo beginInfo = {};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

		vkBeginCommandBuffer(_buffer, &beginInfo);

		return *this;
	}

	void CommandBuffer::EndOneTime(RenderContext& context)
	{
		vkEndCommandBuffer(_buffer);

		VkSubmitInfo submitInfo = {};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &_buffer;

		vkQueueSubmit(context.graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
		vkQueueWaitIdle(context.graphicsQueue);

		context.commandPool.FreeCommandBuffer(context.device, 1, &_buffer);
	}
}