#include "Resolution.hpp"
#include <intrin.h>
Resolution::Resolution(int t_width, int t_height) : width(t_width), height(t_height) {

}
Resolution::Resolution() {
	this->width = 0;
	this->height = 0;
}
Resolution Resolution::operator+(Resolution t_other) {
	return Resolution(this->width + t_other.width, this->height + t_other.width);
}
Resolution Resolution::operator-(Resolution t_other) {
	return Resolution(this->width - t_other.width, this->height - t_other.width);
}
Resolution Resolution::operator*(Resolution t_other) {
	return Resolution(this->width * t_other.width, this->height * t_other.width);
}
Resolution Resolution::operator/(Resolution t_other) {
	return Resolution(this->width / t_other.width, this->height / t_other.width);
}
bool Resolution::operator==(Resolution t_other) {
	return this->width == t_other.width && this->height == t_other.height;
}
bool Resolution::operator!=(Resolution t_other) {
	return this->width != t_other.width || this->height != t_other.height;
}
bool Resolution::operator<(Resolution t_other) {
	return this->width < t_other.width&& this->height < t_other.height;
}
bool Resolution::operator>(Resolution t_other) {
	return this->width > t_other.width && this->height > t_other.height;
}
Resolution Resolution::getAspectRatio() {
	double m_aspectRationWidth;
	uint32_t m_aspectRationHeight = 1;
	m_aspectRationWidth = this->width / this->height;
	while ((m_aspectRationWidth * m_aspectRationHeight) - static_cast<int>(m_aspectRationWidth * m_aspectRationHeight) != 0) {
		m_aspectRationHeight++;
	}
	m_aspectRationWidth *= m_aspectRationHeight;
	return Resolution(static_cast<int>(m_aspectRationWidth), static_cast<int>(m_aspectRationHeight));
}
std::string Resolution::getResolutionAsString() {
	return this->width + "*" + this->height;
}