#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <iostream>
#include <memory>

#include "Cursor.hpp"

struct GLFWwindowDeleter {
	void operator()(GLFWwindow* t_ptr) {
		glfwDestroyWindow(t_ptr);
	}
};

class Window
{
private:
	std::unique_ptr<GLFWwindow, GLFWwindowDeleter> m_window;
	//section metadata
	Resolution m_windowResolution;
	std::string m_windowTitle;
	Image m_windowIcon;
	Cursor m_cursor;
	bool m_windowedMode;
public:
	Window(Config t_config, std::shared_ptr<ImageLoadingScheduler> t_imageLoadingScheduler);
	Window();
	~Window();

	void setWindowTitle(std::string t_windowTitle);
	void setWindowResolution(Resolution t_titleResolution);
	void setWindowIcon(Image t_windowIcon);
	void setWindowedMode(bool t_windowedMode);

	std::string getWindowTitle();
	Resolution getWindowResolution();
	std::shared_ptr<GLFWimage> getWindowIcon();
	GLFWwindow* getWindow();
	bool getWindowedMode();

};
#endif
