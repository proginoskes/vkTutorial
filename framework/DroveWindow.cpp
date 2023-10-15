#include "DroveWindow.hpp"

namespace Drove {
    Window::Window(int width, int height, const char* name) {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        hWind = glfwCreateWindow(width, height, name, nullptr, nullptr);

        glfwSetWindowUserPointer(hWind, this);
        glfwSetFramebufferSizeCallback(hWind, framebufferResizeCallback);

    }
    Window::~Window() {
        glfwDestroyWindow(hWind);

        glfwTerminate();
    }
    bool Window::shouldClose() {
        return glfwWindowShouldClose(hWind);
    }
}
