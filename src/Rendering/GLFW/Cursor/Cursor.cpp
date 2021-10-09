#include "Cursor.hpp"

Cursor::Cursor(Config t_config, std::shared_ptr<ImageLoadingScheduler> t_imageLoadingScheduler) {
	ConfigEntry m_cursorImageIDEntry = t_config.getConfigEntry("CursorImageID");
	if (m_cursorImageIDEntry.value != "") {
		if (std::stoi(m_cursorImageIDEntry.value) != 0x0) {
			this->m_cursorImageID = std::stoi(m_cursorImageIDEntry.value);
			this->m_cursor.reset(glfwCreateStandardCursor(this->m_cursorImageID));
			this->m_cursorImage = Image();
		}
	}
	else {
		ConfigEntry m_cursorImagePathEntry = t_config.getConfigEntry("CursorImagePath");
		this->m_cursorImage = Image(m_cursorImagePathEntry.value,t_imageLoadingScheduler);

		ConfigEntry m_cursorHotspotXEntry = t_config.getConfigEntry("CursorHotspotX");
		ConfigEntry m_cursorHotspotYEntry = t_config.getConfigEntry("CursorHotspotY");
		this->m_cursorHotspot = glm::vec2(std::stoi(m_cursorHotspotXEntry.value), std::stoi(m_cursorHotspotYEntry.value));

		this->m_cursor.reset(glfwCreateCursor(this->m_cursorImage.getGLFWImage().get(), static_cast<int>(this->m_cursorHotspot.x), static_cast<int>(this->m_cursorHotspot.y)));

	}
}
Cursor::Cursor() {
	this->m_cursor = nullptr;
	this->m_cursorImage = Image();
	this->m_cursorImageID = 0x0;
	this->m_cursorHotspot = glm::vec2();
}
Cursor::~Cursor() {

}

glm::vec2 Cursor::getCursorHotspot() {
	return m_cursorHotspot;
}
std::shared_ptr<GLFWimage> Cursor::getCursorImage() {
	return this->m_cursorImage.getGLFWImage();
}
int Cursor::getCursorImageID() {
	return this->m_cursorImageID;
}
GLFWcursor* Cursor::getCursor() {
	return this->m_cursor.get();
}

void Cursor::setCursor(std::unique_ptr<GLFWcursor, GLFWcursorDeleter> t_cursor) {
	this->m_cursor = std::move(t_cursor);
}
void Cursor::setCursorImage(Image t_cursorImage) {
	this->m_cursorImage = t_cursorImage;
	this->m_cursor.reset(glfwCreateCursor(this->m_cursorImage.getGLFWImage().get(), static_cast<int>(this->m_cursorHotspot.x), static_cast<int>(this->m_cursorHotspot.y)));
}
void Cursor::setCursorImageID(int t_cursorImageID) {
	this->m_cursorImageID = t_cursorImageID;
	this->m_cursor.reset(glfwCreateStandardCursor(this->m_cursorImageID));
}
void Cursor::setCursorHotspot(glm::vec2 t_cursorHotspot) {
	this->m_cursorHotspot = t_cursorHotspot;
	this->m_cursor.reset(glfwCreateCursor(this->m_cursorImage.getGLFWImage().get(), static_cast<int>(this->m_cursorHotspot.x), static_cast<int>(this->m_cursorHotspot.y)));
}
Cursor& Cursor::operator=(const Cursor&){
	return *this;
}