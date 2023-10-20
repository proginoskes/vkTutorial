#include "DroveDebugger.hpp"

namespace Drove {

    VkResult Debugger::CreateDebugUtilsMessengerEXT(
        VkInstance* instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
        const VkAllocationCallbacks* pAllocator
    ) {
        PFN_vkCreateDebugUtilsMessengerEXT func
            = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
                *instance, "vkCreateDebugUtilsMessengerEXT"
            );

        if (func != nullptr) {
            return func(*instance, pCreateInfo, pAllocator, &debugMessenger);
        } else {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    }

    void Debugger::DestroyDebugUtilsMessengerEXT(
        VkInstance* instance, const VkAllocationCallbacks* pAllocator
    ) {
        PFN_vkDestroyDebugUtilsMessengerEXT func
            = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
                *instance, "vkDestroyDebugUtilsMessengerEXT"
            );
        if (func != nullptr) {
            func(*instance, debugMessenger, pAllocator);
        }
    }

    bool Debugger::checkValidationLayerSupport() {
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
        for (const char* layerName : validationLayers) {
            bool layerFound = false;

            for (const VkLayerProperties& layerProperties : availableLayers) {
                if (strcmp(layerName, layerProperties.layerName) == 0) {
                    layerFound = true;
                    break;
                }
            }

            if (!layerFound) {
                return false;
            }
        }

        return true;
    }

    void Debugger::resizeFramebuffer(int width, int height) {
        app.resizeFramebuffer(width, height);
    }

    void Debugger::run() {
        app.run();
    }

    Debugger::Debugger(int width, int height,
		std::function<void(int*, int*)> getWindowExtent,
        std::function<void(VkInstance*, VkSurfaceKHR*)> createSurface,
        uint32_t layerCount, const char** ppLayerCount,
        uint32_t extensionCount, const char** ppExtensions,
        void* pNext
    ) : app(width, height, "Drove Debug App", getWindowExtent, createSurface,
        layerCount, ppLayerCount, extensionCount, ppExtensions,
        pNext
    ) {
        if (!checkValidationLayerSupport()) {
            throw std::runtime_error("validation layers requested, but not available!");
        }

        if (CreateDebugUtilsMessengerEXT(
                app.getInstance(), 
                (VkDebugUtilsMessengerCreateInfoEXT*)pNext, 
                nullptr
            ) != VK_SUCCESS
        ) {
            throw std::runtime_error("failed to set up debug messenger!");
        }
    }
    Debugger::~Debugger() {
        DestroyDebugUtilsMessengerEXT(app.getInstance(), nullptr);
    }
}
