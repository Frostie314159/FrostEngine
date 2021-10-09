#include "Config.hpp"


void Config::addConfigKey(ConfigEntry t_configKey){
	this->m_configEntries.push_back(t_configKey);
}
ConfigEntry Config::getConfigEntry(std::string t_configKey) {
	std::vector<ConfigEntry>::iterator m_result = std::find_if(this->m_configEntries.begin(), this->m_configEntries.end(), [&](ConfigEntry t_currentConfigEntry) {
		return t_currentConfigEntry.key == t_configKey;
	});
	return (m_result == this->m_configEntries.end()) ? ConfigEntry() : *m_result;
}

const std::vector<ConfigEntry> Config::getConfigEntries() {
	return this->m_configEntries;
}
