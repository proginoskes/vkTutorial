#include "DroveWindow.hpp"

namespace Drove {
    Window::Window(int width, int height, const char* name) {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        window = glfwCreateWindow(width, height, name, nullptr, nullptr);

        glfwSetWindowUserPointer(window, this);
        glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);

    }
    Window::~Window() {
        glfwDestroyWindow(window);

        glfwTerminate();
    }

    bool Window::shouldClose() {
        return glfwWindowShouldClose(window);
    }
}
