#pragma once

#include "iDroveInstance.hpp"
#include "DroveApp.hpp"

#include <vector>
#include <iostream>
#include <cstdint>

namespace Drove {
	const std::vector<const char*> validationLayers = {
		"VK_LAYER_KHRONOS_validation"
	};

	/**
	*
	* A wrapper around App that is capable of tracking
	* debug-sensitive events.
	*
	*/
	class Debugger : public Instance {
	private:
		// normal class members
		App app;
		VkDebugUtilsMessengerEXT debugMessenger;


		bool checkValidationLayerSupport();
		VkResult CreateDebugUtilsMessengerEXT(
			VkInstance* instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
			const VkAllocationCallbacks* pAllocator
		);
		void DestroyDebugUtilsMessengerEXT(
			VkInstance* instance,const VkAllocationCallbacks* pAllocator
		);

	public:
		//callbacks
		static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
			VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
			VkDebugUtilsMessageTypeFlagsEXT messageType,
			const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
			void* pUserData
		) {

			std::cerr << "validation layer: " << pCallbackData->pMessage;
			if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
				std::cerr << " ~HIGH SEVERITY~";
			}
			std::cerr << std::endl;
			return VK_FALSE;
		};
		// normal class members
		void resizeFramebuffer(int width, int height);
		void run();
		Debugger(int width, int height,
			std::function<void(VkInstance*, VkSurfaceKHR*)> createSurface,
			uint32_t layerCount, const char** ppLayers,
			uint32_t extensionCount, const char** ppExtensions,
			void* pNext
		);
		~Debugger();
	};
}
