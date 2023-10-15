
#include "framework/Drove.hpp"

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

#ifndef NDEBUG
    std::vector<const char*> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };

    std::vector<const char*> extensions(
        glfwExtensions, glfwExtensions + glfwExtensionCount
    );
    extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);


    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
    debugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    debugCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT
        | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT
        | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    debugCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT
        | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT
        | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    debugCreateInfo.pfnUserCallback = Drove::Debugger::debugCallback;
    debugCreateInfo.pUserData = nullptr;

    Drove::Debugger app(
        START_WIDTH, START_HEIGHT,
        static_cast<uint32_t>(validationLayers.size()),
        validationLayers.data(),
        static_cast<uint32_t>(extensions.size()),
        extensions.data(),
        &debugCreateInfo
    );
#else
    Drove::App app(
        START_WIDTH,START_HEIGHT, NAME,
        0, nullptr,
        glfwExtensionCount, glfwExtensions,
        nullptr
    );
#endif // !NDEBUG


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
