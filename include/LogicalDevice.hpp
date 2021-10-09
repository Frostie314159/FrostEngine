#ifndef LOGICAL_DEVICE_HPP_
#define LOGICAL_DEVICE_HPP_

#include "Instance.hpp"
#include "VulkanObject.hpp"

class LogicalDevice :public VulkanObject
{
private:
	VkDevice m_device;
	VkDeviceCreateInfo m_deviceCreateInfo;
	void createDeviceCreateInfo(Config t_config);
public:
	LogicalDevice(Instance t_instance, Config t_config);
	LogicalDevice(const LogicalDevice&);
	LogicalDevice();
	~LogicalDevice();

	const std::type_info& getUnderlyingType();

	void destroy(VkInstance t_instance = VkInstance{}, VkDevice t_logicalDevice = VkDevice{}) override;

	const std::string getObjectName();
};

#endif