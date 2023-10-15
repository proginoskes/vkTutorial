#pragma once

#include "DroveApp.hpp"

#include <GLFW/glfw3.h>

#include <cstdint>


/*

	TODO: HANDLE MINIMIZATION (VkTutorial)

	int width = 0, height = 0;
	glfwGetFramebufferSize(window, &width, &height);
	while (width == 0 || height == 0) {
		glfwGetFramebufferSize(window, &width, &height);
		glfwWaitEvents();
	}
    vkDeviceWaitIdle(device);

*/

namespace Drove {
	class Window {
	private:
		GLFWwindow* hWind;

		//callback
		static void framebufferResizeCallback(GLFWwindow* window, int width, int height) {
			App* app = reinterpret_cast<App*>(glfwGetWindowUserPointer(window));
			// maybe put loop here with app->pause?
			app->resizeFramebuffer(width, height);
		}

	public:
		Window(int width, int height, const char* name);
		~Window();

		bool shouldClose();
	};
}
