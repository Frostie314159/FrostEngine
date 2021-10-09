#include "OpenGLUtil.hpp"

Version OpenGLUtil::getOpenGLVersion() {
	std::string m_versionString = std::string(reinterpret_cast<const char*>(glGetString(GL_VERSION)));
	Version m_temp;
	return Version(std::stoi(m_versionString.substr(0, 1)), std::stoi(m_versionString.substr(2, 1)), std::stoi(m_versionString.substr(4, 1)));
}