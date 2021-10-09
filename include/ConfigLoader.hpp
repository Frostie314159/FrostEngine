#pragma once

#ifndef CONFIG_LOADER_HPP_
#define CONFIG_LOADER_HPP_
#include "Config.hpp"
#include "File.hpp"
#include "json/json.hpp"
using nlohmann::json;

class ConfigLoader {
public:
	static const Config loadConfigFile(std::filesystem::path t_configFilePath);
};

#endif