#include "Layer.hpp"

std::vector<VkLayerProperties> Layer::enumerateLayers(VkPhysicalDevice t_physicalDevice) {
	uint32_t m_layerCount;
	ErrorHandler::handleVulkanErrorCode((t_physicalDevice == VkPhysicalDevice{}) ? vkEnumerateInstanceLayerProperties(&m_layerCount, nullptr) : vkEnumerateDeviceLayerProperties(t_physicalDevice, &m_layerCount, nullptr));

	std::vector<VkLayerProperties> m_layerProperties(m_layerCount);

	ErrorHandler::handleVulkanErrorCode((t_physicalDevice == VkPhysicalDevice{}) ? vkEnumerateInstanceLayerProperties(&m_layerCount, m_layerProperties.data()) : vkEnumerateDeviceLayerProperties(t_physicalDevice, &m_layerCount, m_layerProperties.data()));
	
	return m_layerProperties;
}

std::vector<VkLayerProperties> Layer::getRequieredLayersFromConfig(LayerLevel t_layerLevel, Config t_engineConfig) {
	return {};
}

std::vector<const char*> Layer::getLayerPropertiesAsCStrVector(std::vector<VkLayerProperties> t_layerProperties) {
	std::vector<const char*> m_tempVector(t_layerProperties.size());
	std::for_each(t_layerProperties.begin(), t_layerProperties.end(), [&](VkLayerProperties t_currentLayerProperties) {
		m_tempVector.push_back(t_currentLayerProperties.layerName);
	});
	return m_tempVector;
}