#ifndef PHYSICAL_DEVICE_HPP_
#define PHYSICAL_DEVICE_HPP_

#include <iostream>
#include <string>

#include "vulkan/vulkan.h"
#include "ErrorHandler.hpp"
#include "Config.hpp"
#include "Layer.hpp"
#include "Extension.hpp"
#include "Instance.hpp"
#include "Version.hpp"
#include "BitMaskUtil.hpp"

class PhysicalDevice
{
private:
	VkPhysicalDevice m_physicalDevice;
	VkPhysicalDeviceProperties m_physicalDeviceProperties;
	VkPhysicalDeviceFeatures m_physicalDeviceFeatures;
	VkPhysicalDeviceMemoryProperties m_physicalDeviceMemoryProperties;

	std::vector<VkLayerProperties> m_physicalDeviceLayerProperties;
	std::vector<VkExtensionProperties> m_physicalDeviceExtensionProperties;
	
	void enumeratePhysicalDeviceDetails();
	const std::string getDeviceTypeAsString();
	const std::string getMemoryTypeAsString(VkMemoryType t_memoryType);
public:
	static const std::vector<PhysicalDevice> enumeratePhyiscalDevices(Instance& t_instance);
	static const PhysicalDevice& pickBestPhyiscalDevice(std::vector<PhysicalDevice>& t_phyiscalDevices);
	PhysicalDevice(const VkPhysicalDevice& t_physicalDevice);
	PhysicalDevice(const PhysicalDevice&);
	PhysicalDevice();
	~PhysicalDevice();
	const std::tuple<VkPhysicalDeviceProperties, VkPhysicalDeviceFeatures, VkPhysicalDeviceMemoryProperties> getPhyiscalDeviceDetails();
	void printPhysicalDeviceDetails();
};

#endif