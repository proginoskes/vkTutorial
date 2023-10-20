#pragma once

#include "Drove.hpp"

#include <GLFW/glfw3.h>

#ifndef __GNU_LINUX__
#define GLFW_EXPOSE_NATIVE_WIN32
#else
#define GLFW_EXPOSE_NATIVE_X11
#endif // !__GNU_LINUX__


#include <GLFW/glfw3native.h>

#include <cstdint>
#include <functional>

namespace Drove {
	class Window {
	private:
		GLFWwindow* window;

		//callback
		static void framebufferResizeCallback(GLFWwindow* window, int width, int height) {
			App* app = reinterpret_cast<App*>(glfwGetWindowUserPointer(window));
			// maybe put loop here with app->pause?
			app->resizeFramebuffer(width, height);
		}
        
	public:
		Window(int width, int height, const char* name);
		~Window();

        std::function<void(int*, int*)> getWindowExtent = [this]
            (int* pWidth, int* pHeight){
                glfwGetFramebufferSize(window, pWidth, pHeight);
        };
		
		std::function<void(VkInstance*, VkSurfaceKHR*)> createSurface = [this](
                VkInstance* instance, VkSurfaceKHR* surface
        ) {
			if (glfwCreateWindowSurface(*instance, window, nullptr, surface) != VK_SUCCESS) {
				throw std::runtime_error("failed to create window surface!");
			}
		};
		

		bool shouldClose();
	};
}
