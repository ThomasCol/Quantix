#ifndef __FRAMEBUFFERS_H__
#define __FRAMEBUFFERS_H__

#include <Type.h>

namespace Quantix::Core::Render
{
	struct RenderFramebuffer
	{
		QXuint FBO = 0;
		QXuint texture[2];
		QXuint depthBuffer = 0;
	};

	struct Framebuffer
	{
		QXuint FBO = 0;
		QXuint texture = 0;
		QXuint depthBuffer = 0;
	};

	struct BlurFramebuffer
	{
		QXuint FBO[2];
		QXuint texture[2];
	};
}

#endif //__FRAMEBUFFERS_H__