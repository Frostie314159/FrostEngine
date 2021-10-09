#include "LogicalDevice.hpp"

LogicalDevice::LogicalDevice(Instance t_instance, Config t_config) {

}

const std::type_info& LogicalDevice::getUnderlyingType() {
	return typeid(VkDevice);
}

void LogicalDevice::destroy(VkInstance t_instance, VkDevice t_logicalDevice) {
	vkDestroyDevice(this->m_device, nullptr);
}
void LogicalDevice::createDeviceCreateInfo(Config t_config) {
	
}