#include "GLFWUtil.hpp"

/*
GLFWimage GLFWUtil::loadGLFWImage(std::filesystem::path t_imagePath) {
	GLFWimage m_tempImage;
	m_tempImage.pixels = stbi_load(t_imagePath.string().c_str(), &m_tempImage.width, &m_tempImage.height, 0, STBI_rgb_alpha);
	if (stbi_failure_reason() != nullptr){
		std::cout << stbi_failure_reason() << std::endl;
	}
	if (m_tempImage.pixels == nullptr)
		std::cout << "Error loading Image" << std::endl;
	stbi__g_failure_reason = "";
	return m_tempImage;
}

std::future<GLFWimage> GLFWUtil::loadGLFWImageASync(std::filesystem::path t_imagePath) {
	return std::async(GLFWUtil::loadGLFWImage, t_imagePath);
}
*/