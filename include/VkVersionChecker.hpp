#ifndef VK_VERSION_CHECKER_HPP_
#define VK_VERSION_CHECKER_HPP_

#include "vulkan/vulkan.h"
#include "ErrorHandler.hpp"

namespace VkVersionChecker
{
	uint32_t getVulkanVersion();
};

#endif