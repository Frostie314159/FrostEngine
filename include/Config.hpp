#ifndef CONFIG_HPP_
#define CONFIG_HPP_

#include <iostream>
#include <vector>
#include <algorithm>
#include "json/json.hpp"

using nlohmann::json;
// This struct stores information about config entries.
class ConfigEntry {
public:
	std::string key; //The key of the config entry
	std::string value; //The value of the config entry
	json::value_t valueType; //The type of the value
	ConfigEntry() {
		this->key = "";
		this->value = "";
		this->valueType = json::value_t::null;
	}
};

class Config {
private:
	std::vector<ConfigEntry> m_configEntries;
public:
	void addConfigKey(ConfigEntry t_configEntry);
	ConfigEntry getConfigEntry(std::string t_configKey);
	const std::vector<ConfigEntry> getConfigEntries();
};

#endif 