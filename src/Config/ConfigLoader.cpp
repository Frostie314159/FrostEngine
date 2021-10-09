#include "ConfigLoader.hpp"


const Config ConfigLoader::loadConfigFile(std::filesystem::path t_configFilePath) {
	File m_jsonFile = File(t_configFilePath, std::fstream::in);// Open the Json File with reading enabled
	
	json m_configJson = json::parse(m_jsonFile.readWholeFile()); 
	m_jsonFile.close();

	Config m_Config = Config();
	for (auto& m_iterator : m_configJson.items()) {
		ConfigEntry m_configEntry = ConfigEntry();
		auto m_key = m_iterator.key();
		auto m_value = m_iterator.value();
		m_configEntry.key = m_iterator.key();
		m_configEntry.valueType = m_iterator.value().type();
		
		if (m_configEntry.valueType == json::value_t::number_integer) {
			m_configEntry.value = std::to_string(m_iterator.value().get<int>());
		}
		else if (m_configEntry.valueType == json::value_t::number_float) {
			m_configEntry.value = std::to_string(m_iterator.value().get<float>());
		}
		else if (m_configEntry.valueType == json::value_t::number_unsigned) {
			m_configEntry.value = std::to_string(m_iterator.value().get<uint64_t>());
		}
		else if (m_configEntry.valueType == json::value_t::boolean) {
			m_configEntry.value = std::to_string(m_iterator.value().get<bool>());
		}
		else if(m_configEntry.valueType == json::value_t::string){
			m_configEntry.value = m_iterator.value().get<std::string>();
		}
		else {
			std::cerr << "Unsupported JSON type" << std::endl;
		}
		
		m_Config.addConfigKey(m_configEntry);
	}
	return m_Config;
}