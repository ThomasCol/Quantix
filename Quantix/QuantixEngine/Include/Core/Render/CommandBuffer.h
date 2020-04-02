#pragma once

#include <vulkan/vulkan.h>
#include <vector>

namespace Quantix::Core::Render
{
	class CommandPool;
	class RenderContext;

	class CommandBuffer
	{
	public:
		CommandBuffer() = default;
		~CommandBuffer() = default;

		CommandBuffer& BeginOneTime(RenderContext& context);
		void EndOneTime(RenderContext& context);

		VkCommandBuffer& Get() { return _buffer; }

	private:
		VkCommandBuffer _buffer;

	};
}