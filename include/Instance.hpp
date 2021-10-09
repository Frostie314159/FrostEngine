#ifndef INSTANCE_HPP_
#define INSTANCE_HPP_

#include "Config.hpp"
#include "File.hpp"
#include "Layer.hpp"
#include "Extension.hpp"
#include "vulkan/vulkan.h"
#include "VkVersionChecker.hpp"
#include "VulkanObject.hpp"

class Instance :public VulkanObject 
{
private:
	VkInstance m_instance;

	VkApplicationInfo m_appInfo;
	VkInstanceCreateInfo m_instanceCreateInfo;

	bool m_destroyed = false;

	std::vector<VkLayerProperties> m_instanceLayers;
	std::vector<VkExtensionProperties> m_instanceExtensions;
	std::vector<const char*> m_enabledLayers;
	std::vector<const char*> m_enabledExtensions;
	
	void createApplicationInfo(Config t_config);
	void createInstanceCreateInfo(Config t_config);
public:
	Instance(Config t_config);
	Instance(const Instance&);
	Instance();
	~Instance();

	const std::type_info& getUnderlyingType();
	
	void createInstance(Config t_config);
	void destroy(VkInstance t_instance = VkInstance{}, VkDevice t_logicalDevice = VkDevice{}) override;
	
	const VkInstance& getInstance();
	const std::string getObjectName();
};

#endif