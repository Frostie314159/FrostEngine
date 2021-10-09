#include "Extension.hpp"

std::vector<VkExtensionProperties> Extension::enumerateExtensions(VkPhysicalDevice t_physicalDevice) {
	uint32_t m_extensionCount;

	ErrorHandler::handleVulkanErrorCode((t_physicalDevice == VkPhysicalDevice{}) ? vkEnumerateInstanceExtensionProperties(nullptr, &m_extensionCount, nullptr) : vkEnumerateDeviceExtensionProperties(t_physicalDevice, nullptr, &m_extensionCount, nullptr));

	std::vector<VkExtensionProperties> m_extensionProperties(m_extensionCount);

	ErrorHandler::handleVulkanErrorCode((t_physicalDevice == VkPhysicalDevice{}) ? vkEnumerateInstanceExtensionProperties(nullptr, &m_extensionCount, m_extensionProperties.data()) : vkEnumerateDeviceExtensionProperties(t_physicalDevice, nullptr, &m_extensionCount, m_extensionProperties.data()));

	return m_extensionProperties;
}

std::vector<const char*> Extension::getExtensionPropertiesAsCStrVector(std::vector<VkExtensionProperties> t_extensionProperties) {
	std::vector<const char*> m_tempVector(t_extensionProperties.size());
	std::for_each(t_extensionProperties.begin(), t_extensionProperties.end(), [&](VkExtensionProperties t_currentExtensionProperties) {
		m_tempVector.push_back(t_currentExtensionProperties.extensionName);
	});
	return m_tempVector;
}