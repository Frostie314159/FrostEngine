#ifndef VULKAN_OBJECT_MANAGER_HPP_
#define VULKAN_OBJECT_MANAGER_HPP_

#include <iostream>
#include <vector>
#include <memory>
#include "VulkanObject.hpp"

class VulkanObjectManager
{
	std::vector<VulkanObject> m_vulkanObjectList;
public:
	VulkanObjectManager();
	~VulkanObjectManager();
	size_t createVulkanObject(VulkanObject& t_vulkanObject);
	void destroyObjects();
};

#endif