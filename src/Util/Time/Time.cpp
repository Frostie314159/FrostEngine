#include "Time.hpp"

std::string Time::getTimeAsString() {
	auto m_time = std::time(nullptr);
	auto m_timeStructure = *std::localtime(&m_time);
	return ((m_timeStructure.tm_hour < 10) ? ("0" + std::to_string(m_timeStructure.tm_hour)) : std::to_string(m_timeStructure.tm_hour)) + ":" + ((m_timeStructure.tm_min < 10) ? ("0" + std::to_string(m_timeStructure.tm_min)) : std::to_string(m_timeStructure.tm_min)) + ":" + ((m_timeStructure.tm_sec < 10) ? ("0" + std::to_string(m_timeStructure.tm_sec)) : std::to_string(m_timeStructure.tm_sec));
}
