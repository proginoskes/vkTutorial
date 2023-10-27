#pragma once

#include "iDroveInstance.hpp"
#include "DrovePipeline.hpp"


#include <iostream>
#include <stdexcept>
#include <vector>
#include <optional>
#include <set>
#include <cstdint>
#include <limits>
#include <algorithm>

#include <vulkan/vulkan_core.h>

namespace Drove {
	struct QueueFamilyIndices {
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;
		bool isComplete() {
			return graphicsFamily.has_value()
				&& presentFamily.has_value();
		}
	};
    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };
    const std::vector<const char*> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };
	class App : public Instance {
	private:
		VkInstance instance;
		VkSurfaceKHR surface;

		VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
		VkDevice device;

		VkQueue graphicsQueue;
		VkQueue presentQueue;

        VkSwapchainKHR swapChain;
        std::vector<VkImage> swapChainImages;
        std::vector<VkImageView> swapChainImageViews;
        VkFormat swapChainImageFormat;
        VkExtent2D swapChainExtent;
        
        Pipeline* pipeline = nullptr;

		void pickPhysicalDevice();
		bool isDeviceSuitable(VkPhysicalDevice device);
		QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
		void createLogicalDevice(uint32_t layerCount, const char** ppLayers);
        bool checkDeviceExtensionSupport(VkPhysicalDevice device);
        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
	    VkSurfaceFormatKHR chooseSwapSurfaceFormat(
                const std::vector<VkSurfaceFormatKHR>& availableFormats
            ); 	
        VkPresentModeKHR chooseSwapPresentMode(
                const std::vector<VkPresentModeKHR>& availablePresentModes
            );
        VkExtent2D chooseSwapExtent(
                const VkSurfaceCapabilitiesKHR& capabilities,
			    std::function<void(int*, int*)> getWindowExtent
            );  
        void createSwapChain(
                std::function<void(int*, int*)> getWindowExtent
            );
        void createImageViews();
    public:
		App(int width, int height, const char* name,
			std::function<void(int*, int*)> getWindowExtent,
			std::function<void(VkInstance*, VkSurfaceKHR*)> createSurface,
			uint32_t layerCount, const char** ppLayers,
			uint32_t extensionCount, const char** ppExtensions,
			void* pNext
		);
		~App();

		void resizeFramebuffer(int width, int height);
		void run();


		VkInstance* getInstance();
	};
}
