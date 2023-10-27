// an interface that is used in App and Debugger to make debugger behave like app

#pragma once

#ifdef _WIN32
#define VK_USE_PLATFORM_WIN32_KHR
#else
#define VK_USE_PLATFORM_X11_KHR
#endif

#include <vulkan/vulkan.h>
#include <functional>

namespace Drove {
	class Instance {
	private:

	public:
		virtual void resizeFramebuffer(int width, int height) = 0;
		virtual void run() = 0;
	};
}
