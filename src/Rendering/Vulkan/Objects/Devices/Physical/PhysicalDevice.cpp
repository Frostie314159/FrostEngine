#include "PhysicalDevice.hpp"

const std::string PhysicalDevice::getDeviceTypeAsString() {
	switch (this->m_physicalDeviceProperties.deviceType) {
	case VK_PHYSICAL_DEVICE_TYPE_OTHER:
		return "Other";
	case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
		return "Integrated GPU";
	case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
		return "Discrete GPU";
	case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
		return "Virtual GPU";
	case VK_PHYSICAL_DEVICE_TYPE_CPU:
		return "CPU";
	default:
		throw std::invalid_argument("Phyiscal Device Type unknown!");
	}
}
const std::string PhysicalDevice::getMemoryTypeAsString(VkMemoryType t_memoryType) {
	std::string m_tempString;
	std::vector<std::string> m_enabledFlags;
	m_tempString += "Heap Index: " + t_memoryType.heapIndex + '\n';
	m_tempString += "Memory Property Flags: ";
	if (BitMaskUtil::isBitInBitMask(t_memoryType.propertyFlags, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)) {
		m_enabledFlags.push_back("VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT");
	}
		
	if (BitMaskUtil::isBitInBitMask(t_memoryType.propertyFlags, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)) {
		m_enabledFlags.push_back("VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT");
	}

	if (BitMaskUtil::isBitInBitMask(t_memoryType.propertyFlags, VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)) {
		m_enabledFlags.push_back("VK_MEMORY_PROPERTY_HOST_COHERENT_BIT");
	}

	if (BitMaskUtil::isBitInBitMask(t_memoryType.propertyFlags, VK_MEMORY_PROPERTY_HOST_CACHED_BIT)) {
		m_enabledFlags.push_back("VK_MEMORY_PROPERTY_HOST_CACHED_BIT");
	}

	if (BitMaskUtil::isBitInBitMask(t_memoryType.propertyFlags, VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT)) {
		m_enabledFlags.push_back("VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT");
	}

	if (BitMaskUtil::isBitInBitMask(t_memoryType.propertyFlags, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)) {
		m_enabledFlags.push_back("VK_MEMORY_PROPERTY_PROTECTED_BIT");
	}

	if (BitMaskUtil::isBitInBitMask(t_memoryType.propertyFlags, VK_MEMORY_PROPERTY_DEVICE_COHERENT_BIT_AMD)) {
		m_enabledFlags.push_back("VK_MEMORY_PROPERTY_DEVICE_COHERENT_BIT_AMD");
	}

	if (BitMaskUtil::isBitInBitMask(t_memoryType.propertyFlags, VK_MEMORY_PROPERTY_DEVICE_UNCACHED_BIT_AMD)) {
		m_enabledFlags.push_back("VK_MEMORY_PROPERTY_DEVICE_UNCACHED_BIT_AMD");
	}
	if (m_enabledFlags.size() == 1)
		m_tempString += m_enabledFlags.at(0) + '\n'; 
	else
		for (size_t i = 0; i < m_enabledFlags.size(); i++) {
			m_tempString += m_enabledFlags.at(i);
			if (i != m_enabledFlags.size() - 1)
				m_tempString += " | ";
		}
	m_tempString += '\n';
	return m_tempString;
}

PhysicalDevice::PhysicalDevice(const VkPhysicalDevice& t_physicalDevice) {
	this->enumeratePhysicalDeviceDetails();
}
PhysicalDevice::PhysicalDevice(const PhysicalDevice&) {

}
PhysicalDevice::PhysicalDevice() {

}
PhysicalDevice::~PhysicalDevice(){

}

const std::vector<PhysicalDevice> PhysicalDevice::enumeratePhyiscalDevices(Instance& t_instance){
	uint32_t m_physicalDeviceCount;
	
	ErrorHandler::handleVulkanErrorCode(vkEnumeratePhysicalDevices(t_instance.getInstance(), &m_physicalDeviceCount, nullptr));

	std::vector<VkPhysicalDevice> m_tempPhysicalDevices(m_physicalDeviceCount);

	ErrorHandler::handleVulkanErrorCode(vkEnumeratePhysicalDevices(t_instance.getInstance(), &m_physicalDeviceCount, m_tempPhysicalDevices.data()));

	std::vector<PhysicalDevice> m_physicalDevices(m_physicalDeviceCount);

	std::for_each(m_tempPhysicalDevices.begin(), m_tempPhysicalDevices.end(), [&](VkPhysicalDevice t_currentPhysicalDevice) {
		m_physicalDevices.push_back(PhysicalDevice(t_currentPhysicalDevice));
	});
	return m_physicalDevices;
}
const PhysicalDevice& PhysicalDevice::pickBestPhyiscalDevice(std::vector<PhysicalDevice>& t_physicalDevices) {
	//TODO this is totally dumb
	VkDeviceSize m_maxHeapSize = 0;
	size_t m_bestPhysicalDevice = 0;

	if(t_physicalDevices.size() > 1)
		for (size_t i = 0; i < t_physicalDevices.size();++i) {
			VkPhysicalDeviceMemoryProperties m_currentMemoryProperties = std::get<2>(t_physicalDevices.at(i).getPhyiscalDeviceDetails());
			VkDeviceSize m_currentHeapSize = 0;
			for (uint32_t i = 0; i < m_currentMemoryProperties.memoryHeapCount; ++i)
				m_currentHeapSize += m_currentMemoryProperties.memoryHeaps[i].size;
			if (m_currentHeapSize >= m_maxHeapSize) {
				m_maxHeapSize = m_currentHeapSize;
				m_bestPhysicalDevice = i;
			}
		};
	return t_physicalDevices.at(m_bestPhysicalDevice);
}

void PhysicalDevice::enumeratePhysicalDeviceDetails() {
	vkGetPhysicalDeviceProperties(this->m_physicalDevice, &this->m_physicalDeviceProperties);
	vkGetPhysicalDeviceFeatures(this->m_physicalDevice, &this->m_physicalDeviceFeatures);
	this->m_physicalDeviceLayerProperties = Layer::enumerateLayers(this->m_physicalDevice);
	this->m_physicalDeviceExtensionProperties = Extension::enumerateExtensions(this->m_physicalDevice);
}

const std::tuple<VkPhysicalDeviceProperties, VkPhysicalDeviceFeatures, VkPhysicalDeviceMemoryProperties> PhysicalDevice::getPhyiscalDeviceDetails() {
	return std::make_tuple(this->m_physicalDeviceProperties, this->m_physicalDeviceFeatures, this->m_physicalDeviceMemoryProperties);
}
void PhysicalDevice::printPhysicalDeviceDetails() {
	std::cout << "Physical Device Properties: " << std::endl << std::endl;
	std::cout << "API Version: " << Version(this->m_physicalDeviceProperties.apiVersion).getVersionAsString() << std::endl;
	std::cout << "Driver Version: " << this->m_physicalDeviceProperties.driverVersion << std::endl;
	std::cout << "Vendor ID: " << this->m_physicalDeviceProperties.vendorID << std::endl;
	std::cout << "Device ID: " << this->m_physicalDeviceProperties.deviceID << std::endl;
	std::cout << "Device Type: " << this->getDeviceTypeAsString() << std::endl;
	std::cout << "Device Name: " << this->m_physicalDeviceProperties.deviceName << std::endl;
	std::cout << "Pipeline Cache UUID: " << this->m_physicalDeviceProperties.pipelineCacheUUID << std::endl;
	
	std::cout << "Physical Device Limits: " << std::endl << std::endl;
	std::cout << "Amount of Memory Types: " << this->m_physicalDeviceMemoryProperties.memoryTypeCount << std::endl;
	std::for_each(std::begin(this->m_physicalDeviceMemoryProperties.memoryTypes), std::end(this->m_physicalDeviceMemoryProperties.memoryTypes), [&](VkMemoryType t_memoryType) {
		std::cout << this->getMemoryTypeAsString(t_memoryType);
	});
}