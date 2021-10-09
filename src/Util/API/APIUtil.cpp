#include "APIUtil.hpp"

GraphicsAPI APIUtil::getAPIByCascade() {
	if (glfwVulkanSupported()) {
		return GraphicsAPI::GRAPHICS_API_VULKAN;
	}
	return GraphicsAPI::GRAPHICS_API_OPENGL;
}