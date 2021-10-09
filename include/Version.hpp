#ifndef VERSION_HPP_
#define VERSION_HPP_

#include <iostream>
#include <string>

class Version
{
private:

	uint32_t m_major, m_minor, m_patch;

public:

	Version(uint32_t t_version);
	Version(uint32_t t_versionMajor, uint32_t t_versionMinor, uint32_t t_versionPatch);
	Version(const Version&);
	Version();
	~Version();

	std::string getVersionAsString();

	uint32_t getMajorVersion();
	uint32_t getMinorVersion();
	uint32_t getPatchVersion();

	uint32_t getVersionNumber();

};

#endif