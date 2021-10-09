#ifndef CURSOR_HPP_
#define CURSOR_HPP_

#include <iostream>
#include <memory>

#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "Config.hpp"
#include "Resolution.hpp"
#include "Image.hpp"

struct GLFWcursorDeleter {

	void operator()(GLFWcursor* t_ptr) {
		glfwDestroyCursor(t_ptr);
	}

};

class Cursor
{
private:
	std::unique_ptr<GLFWcursor, GLFWcursorDeleter> m_cursor;
	Image   	m_cursorImage;
	int		    m_cursorImageID = 0x0;
	glm::vec2   m_cursorHotspot;
public:
	Cursor(Config t_config, std::shared_ptr<ImageLoadingScheduler> t_imageLoadingScheduler);
	Cursor(const Cursor&) = default;
	Cursor();
	~Cursor();

	glm::vec2 					getCursorHotspot();
	std::shared_ptr<GLFWimage> 	getCursorImage();
	int 						getCursorImageID();
	GLFWcursor* 				getCursor();

	void setCursor(std::unique_ptr<GLFWcursor, GLFWcursorDeleter> t_cursor);
	void setCursorImage(Image t_cursorImage);
	void setCursorImageID(int t_cursorImageID);
	void setCursorHotspot(glm::vec2 t_cursorHotspot);
	
	Cursor& operator=(const Cursor&);
};

#endif