#include "Settings.h"

void Settings::LoadTranslation()
{
	LoadJSON(translationPath, translationMap);
}

const std::string& Settings::GetTranslation(const std::string& key) const
{
	auto it = translationMap.find(key);
	if (it != translationMap.end()) {
		return it->second;
	}

	static const std::string emptyString;
	return emptyString;
}

void Settings::LoadJSON(const std::string& jsonPath, std::unordered_map<std::string, std::string>& jsonMap)
{
	jsonMap.clear();

	std::ifstream file(jsonPath);
	if (!file.is_open()) {
		SKSE::log::warn("Failed to open JSON file: {}", jsonPath);
		return;
	}

	try {
		nlohmann::json data;
		file >> data;

		for (auto& [key, value] : data.items()) {
			if (value.is_string()) {
				jsonMap[key] = value.get<std::string>();
			}
		}

		SKSE::log::info("JSON file loaded successfully: {}", jsonPath);
	} catch (const nlohmann::json::parse_error& e) {
		SKSE::log::error("Failed to parse JSON file: {}, offset: byte {}, id: {}", jsonPath, e.byte, e.id);
	} catch (const std::exception& e) {
		SKSE::log::error("Failed to load JSON file: {}, {}", jsonPath, e.what());
	}
}
