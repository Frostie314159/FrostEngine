#ifndef API_UTIL_HPP_
#define API_UTIL_HPP_

#include <iostream>

#include "GLFW/glfw3.h"

enum class GraphicsAPI {
	GRAPHICS_API_VULKAN = 0,
	GRAPHICS_API_OPENGL = 1
};

class APIUtil
{
public:
	static GraphicsAPI getAPIByCascade();
};

#endif