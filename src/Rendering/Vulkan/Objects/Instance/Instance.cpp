#include "Instance.hpp"

void Instance::createApplicationInfo(Config t_config) {
	this->m_appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	this->m_appInfo.pNext = nullptr;
	this->m_appInfo.pApplicationName = t_config.getConfigEntry("ApplicationName").value.c_str();
	this->m_appInfo.applicationVersion = 0;
	this->m_appInfo.pEngineName = "FrostEngine";
	this->m_appInfo.engineVersion = 0;
	this->m_appInfo.apiVersion = VkVersionChecker::getVulkanVersion();
}
void Instance::createInstanceCreateInfo(Config t_config) {
	this->createApplicationInfo(t_config);
	this->m_instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	this->m_instanceCreateInfo.pNext = nullptr;
	this->m_instanceCreateInfo.flags = 0x0;
	this->m_instanceCreateInfo.pApplicationInfo = &this->m_appInfo;
	this->m_instanceCreateInfo.enabledLayerCount = static_cast<uint32_t>(this->m_enabledLayers.size());
	this->m_instanceCreateInfo.ppEnabledLayerNames = this->m_enabledLayers.data();
	this->m_instanceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(this->m_enabledExtensions.size());
	this->m_instanceCreateInfo.ppEnabledExtensionNames = this->m_enabledExtensions.data();
}

Instance::Instance(Config t_config) {
	createInstance(t_config);
}
Instance::Instance(const Instance&) {
	this->m_appInfo = VkApplicationInfo();
}
Instance::Instance() {

}
Instance::~Instance() {
	if(!this->m_destroyed)
		this->destroy();
}

void Instance::destroy(VkInstance t_instance, VkDevice t_logicalDevice) {
	vkDestroyInstance(this->m_instance, nullptr);
	this->m_instanceLayers.clear();
	this->m_instanceExtensions.clear();
	this->m_enabledLayers.clear();
	this->m_enabledExtensions.clear();
	this->m_destroyed = true;
}

const std::type_info& Instance::getUnderlyingType() {
	return typeid(VkInstance);
}

void Instance::createInstance(Config t_engineConfig) {
	this->m_instanceLayers = Layer::enumerateLayers();
	this->m_instanceExtensions = Extension::enumerateExtensions();
	createInstanceCreateInfo(t_engineConfig);
	ErrorHandler::handleVulkanErrorCode(vkCreateInstance(&m_instanceCreateInfo, nullptr, &this->m_instance));
}

const VkInstance& Instance::getInstance() {
	return this->m_instance;
}
const std::string getObjectName() {
	return "Instance";
}