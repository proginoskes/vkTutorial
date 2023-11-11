
#include "framework/Drove.hpp"
#include "framework/DroveWindow.hpp"

const char* NAME = "Drove App";
const int START_WIDTH = 800;
const int START_HEIGHT = 600;

int main() {

    Drove::Window window(START_WIDTH, START_HEIGHT, NAME);
    
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;

    glfwExtensions = glfwGetRequiredInstanceExtensions(
        &glfwExtensionCount
    );

    Drove::App app(glfwExtensionCount, glfwExtensions, window.getCreateSurface());

    try {
        //app.run();
        while (!window.shouldClose()) {
            glfwPollEvents();
            //app.drawFrame();
        }
        //app.idle();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
