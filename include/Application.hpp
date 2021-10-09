#ifndef APPLICATION_HPP_
#define APPLICATION_HPP_

#include <iostream>

#include "OpenGLUtil.hpp"
#include "ErrorHandler.hpp"
#include "ConfigLoader.hpp"
#include "Window.hpp"
#include "Timer.hpp"
#include "APIUtil.hpp"
#include "VAO.hpp"
#include "Instance.hpp"

class Application
{
public:
	Application();
	~Application();
	void run();
};

#endif