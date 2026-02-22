#pragma once

class Settings : public REX::Singleton<Settings>
{
public:
	void LoadTranslation();
	const std::string& GetTranslation(const std::string& key) const;

private:
	void LoadJSON(const std::string& jsonPath, std::unordered_map<std::string, std::string>& jsonMap);

	static inline constexpr auto translationPath = "Data/SKSE/Plugins/EnchantingPreserver/Translations.json";
	std::unordered_map<std::string, std::string> translationMap;
};
