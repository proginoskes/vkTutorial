#pragma once


#if _WIN32
#define VK_USE_PLATFORM_WIN32_KHR
#else
#define VK_USE_PLATFORM_X11_KHR
#endif

#include "DroveConstants.hpp"

#include <vulkan/vulkan.h>
#include <stdexcept>
#include <optional>
#include <set>
#include <vector>

namespace Drove {
	const std::vector<const char*> deviceExtensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	struct QueueFamilyIndices {
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;

		bool isComplete() {
			return graphicsFamily.has_value() && presentFamily.has_value();
		}
	};
	struct SwapChainSupportDetails {
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;
	};

	class Device {
	private:
		VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
		VkDevice device;

		VkQueue graphicsQueue;
		VkQueue presentQueue;

		bool isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR* pSurface);
		QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR* pSurface);
		bool checkDeviceExtensionSupport(VkPhysicalDevice device);
		SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR* pSurface);

		void pickPhysicalDevice(VkInstance* pInstance, VkSurfaceKHR* pSurface);
		void createLogicalDevice(VkSurfaceKHR* pSurface);
	public:
		Device(VkInstance* pInstance, VkSurfaceKHR* pSurface);
		~Device();
	};
}