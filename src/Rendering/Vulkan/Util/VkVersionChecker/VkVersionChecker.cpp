#include "VkVersionChecker.hpp"

uint32_t VkVersionChecker::getVulkanVersion() {
	PFN_vkEnumerateInstanceVersion m_enumerateInstanceVersion = reinterpret_cast<PFN_vkEnumerateInstanceVersion>(vkGetInstanceProcAddr(VK_NULL_HANDLE,"vkEnumerateInstanceVersion"));
	uint32_t m_tempVersion = VK_API_VERSION_1_0;
	if (m_enumerateInstanceVersion != nullptr)
		ErrorHandler::handleVulkanErrorCode(vkEnumerateInstanceVersion(&m_tempVersion));
	return m_tempVersion;
}