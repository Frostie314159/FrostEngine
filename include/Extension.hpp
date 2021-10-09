#ifndef EXTENSION_HPP_
#define EXTENSION_HPP_

#include <iostream>
#include <vector>
#include <memory>

#include "vulkan/vulkan.h"
#include "ErrorHandler.hpp"

namespace Extension {

	enum class ExtensionLevel {
		EXTENSION_LEVEL_INSTANCE,
		EXTENSION_LEVEL_DEVICE
	};

	std::vector<VkExtensionProperties> enumerateExtensions(VkPhysicalDevice t_physicalDevice = VkPhysicalDevice{});

	std::vector<const char*> getExtensionPropertiesAsCStrVector(std::vector<VkExtensionProperties> t_extensionProperties);
}

#endif