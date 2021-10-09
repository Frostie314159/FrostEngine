#ifndef VULKAN_OBJECT_HPP_
#define VULKAN_OBJECT_HPP_

#include <iostream>
#include <map>
#include <functional>
#include <typeinfo>

#include "Config.hpp"
#include "vulkan/vulkan.h"

typedef void (*voidFunction)(void);

class VulkanObject
{
public:


	virtual void destroy(VkInstance t_instance, VkDevice t_logicalDevice) = 0;

	void printObjectDetails();

	const std::type_info& getUnderlyingType();
	const std::string getObjectName();
};


#endif