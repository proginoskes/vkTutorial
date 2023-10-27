// an interface that is used in App and Debugger to make debugger behave like app

#pragma once
#define VK_USE_PLATFORM_X11_KHR

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
