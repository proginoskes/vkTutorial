#pragma once


#if _WIN32
#define VK_USE_PLATFORM_WIN32_KHR
#else
#define VK_USE_PLATFORM_X11_KHR
#endif

#include <vulkan/vulkan.h>

#include <functional>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <optional>
#include <set>
#include <cstdint>
#include <limits>
#include <algorithm>


namespace Drove {
	class App {
	private:
		VkInstance instance;
		VkDebugUtilsMessengerEXT debugMessenger;
		VkSurfaceKHR surface;


		static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
			std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

			return VK_FALSE;
		}
		VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
			auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
			if (func != nullptr) {
				return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
			} else {
				return VK_ERROR_EXTENSION_NOT_PRESENT;
			}
		}
		
		const std::vector<const char*> validationLayers = {
			"VK_LAYER_KHRONOS_validation"
		};

		bool checkValidationLayerSupport();

		void createInstance(uint32_t extensionCount, const char** extensions);
		
		// debug stuff
#ifndef NDEBUG
		void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
		void setupDebugMessenger();
#endif

    public:
		App(uint32_t extensionCount, const char** extensions, 
			std::function<void(VkInstance*, VkSurfaceKHR*)> createSurface
		);
		~App();

		/*
		void resizeFramebuffer(int width, int height);
		void run();


		VkInstance* getInstance();
		*/
	};
}
