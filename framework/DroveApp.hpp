#pragma once

#include "iDroveInstance.hpp"

#include <vulkan/vulkan.h>

#include <iostream>
#include <stdexcept>
#include <vector>
#include <optional>

namespace Drove {
	struct QueueFamilyIndices {
		std::optional<uint32_t> graphicsFamily;
		bool isComplete() {
			return graphicsFamily.has_value();
		}
	};
	class App : public Instance {
	private:
		VkInstance instance;

		VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
		VkDevice device;

		VkQueue graphicsQueue;

		void pickPhysicalDevice();
		bool isDeviceSuitable(VkPhysicalDevice device);
		QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
		void createLogicalDevice(uint32_t layerCount, const char** ppLayers);

	public:
		App(int width, int height, const char* name,
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
