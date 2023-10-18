#pragma once

#include "iDroveInstance.hpp"

#include <iostream>
#include <stdexcept>
#include <vector>
#include <optional>
#include <set>

namespace Drove {
	struct QueueFamilyIndices {
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;
		bool isComplete() {
			return graphicsFamily.has_value()
				&& presentFamily.has_value();
		}
	};

	class App : public Instance {
	private:
		VkInstance instance;
		VkSurfaceKHR surface;

		VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
		VkDevice device;

		VkQueue graphicsQueue;
		VkQueue presentQueue;

		void pickPhysicalDevice();
		bool isDeviceSuitable(VkPhysicalDevice device);
		QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
		void createLogicalDevice(uint32_t layerCount, const char** ppLayers);

	public:
		App(int width, int height, const char* name,
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
