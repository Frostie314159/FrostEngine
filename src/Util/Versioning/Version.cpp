#include "Version.hpp"

Version::Version(uint32_t t_version) {
	this->m_major = ((uint32_t)(t_version) >> 22);
	this->m_minor = (((uint32_t)(t_version) >> 12) & 0x3ff);
	this->m_patch = ((uint32_t)(t_version) & 0xfff);
}
Version::Version(uint32_t t_versionMajor, uint32_t t_versionMinor, uint32_t t_versionPatch) {
	this->m_major = t_versionMajor;
	this->m_minor = t_versionMinor;
	this->m_patch = t_versionPatch;
}
Version::Version(const Version&) {
	this->m_major = 0;
	this->m_minor = 0;
	this->m_patch = 0;
}
Version::Version() {
	this->m_major = 0;
	this->m_minor = 0;
	this->m_patch = 0;
}
Version::~Version() {

}

std::string Version::getVersionAsString() {
	return std::to_string(this->m_major) + "." + std::to_string(this->m_minor) + "." + std::to_string(this->m_patch);
}

uint32_t Version::getMajorVersion() {
	return this->m_major;
}
uint32_t Version::getMinorVersion() {
	return this->m_minor;
}
uint32_t Version::getPatchVersion() {
	return this->m_patch;
}

uint32_t Version::getVersionNumber() {
	return ((((uint32_t)(this->m_major)) << 22) | (((uint32_t)(this->m_minor)) << 12) | ((uint32_t)(this->m_patch)));
}