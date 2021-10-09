#ifndef ERROR_HANDLER_HPP_
#define ERROR_HANDLER_HPP_

#include <iostream>

#include "File.hpp"
#include "Time.hpp"
#if  defined _WIN32 || defined __CYGWIN__
	#include <windef.h>
#endif

#include "GL/glew.h"
#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

class ErrorHandler
{
private:
	static std::string getVulkanErrorCodeAsString(VkResult t_errorCode);
	static std::string getGLFWErrorCodeAsString(int t_errorCode);
	static std::string getOpenGLErrorCodeAsString(GLenum t_errorCode);
	static std::string getOpenALErrorCodeAsString(int t_errorCode);
	static void glClearError();
public:
	static void handleVulkanErrorCode(VkResult t_errorCode);
	static void handleGLFWErrorCode(int t_errorCode);
	static void handleOpenGLErrorCode(GLenum t_errorCode);
	static void handleOpenALErrorCode(int t_errorCode);
};

#endif