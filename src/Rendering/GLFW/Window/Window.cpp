#include "Window.hpp"

Window::Window(Config t_config, std::shared_ptr<ImageLoadingScheduler> t_imageLoadingScheduler) {
	ConfigEntry m_windowedModeEntry = t_config.getConfigEntry("WindowedMode");
	std::filesystem::path m_windowIconPath = t_config.getConfigEntry("WindowIconPath").value;
	this->m_windowTitle = t_config.getConfigEntry("WindowTitle").value;
	this->m_windowResolution = Resolution(std::stoi(t_config.getConfigEntry("WindowWidth").value), std::stoi(t_config.getConfigEntry("WindowHeight").value));
	this->m_window.reset(glfwCreateWindow(this->m_windowResolution.width, this->m_windowResolution.height, this->m_windowTitle.c_str(), (std::stoi(m_windowedModeEntry.value) == 1) ? NULL : glfwGetPrimaryMonitor(), NULL));
	this->m_cursor = Cursor(t_config, t_imageLoadingScheduler);
	this->m_windowedMode = std::stoi(m_windowedModeEntry.value) == 1;
	
	if (m_windowIconPath == "") {
		this->m_windowIcon = Image("logo.png", t_imageLoadingScheduler);
	}
	else {
		this->m_windowIcon = Image(m_windowIconPath,t_imageLoadingScheduler);
	}
	glfwSetWindowIcon(this->m_window.get(), 1, this->m_windowIcon.getGLFWImage().get());
	glfwSetCursor(this->m_window.get(), this->m_cursor.getCursor());
}
Window::Window() {
	this->m_window = nullptr;
	this->m_windowedMode = true;
	this->m_windowIcon = Image();
	this->m_windowResolution = Resolution();
	this->m_windowTitle = "Frost Engine";
	this->m_cursor = Cursor();
}
Window::~Window() {

}
void Window::setWindowTitle(std::string t_windowTitle){
	glfwSetWindowTitle(this->m_window.get(), t_windowTitle.c_str());
}
void Window::setWindowResolution(Resolution t_titleResolution){
	glfwSetWindowSize(this->m_window.get(), t_titleResolution.width, t_titleResolution.height);
}
void Window::setWindowIcon(Image t_windowIcon){
	glfwSetWindowIcon(this->m_window.get(), 1, t_windowIcon.getGLFWImage().get());
}
void Window::setWindowedMode(bool t_windowedMode) {
	this->m_windowedMode = t_windowedMode;
	const GLFWvidmode* m_vidMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwSetWindowMonitor(this->m_window.get(), glfwGetPrimaryMonitor(), 0, 0, m_vidMode->width, m_vidMode->height, m_vidMode->refreshRate);
}

std::string Window::getWindowTitle(){
	return this->m_windowTitle;
}
Resolution Window::getWindowResolution(){
	return this->m_windowResolution;
}
std::shared_ptr<GLFWimage> Window::getWindowIcon(){
	return this->m_windowIcon.getGLFWImage();
}
GLFWwindow* Window::getWindow(){
	return this->m_window.get();
}
bool Window::getWindowedMode() {
	return this->m_windowedMode;
}