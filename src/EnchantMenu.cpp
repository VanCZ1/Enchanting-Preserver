#include "EnchantMenu.h"
#include "Settings.h"

namespace EnchantMenu
{
	static void SetGameSettingString(RE::Setting* a_setting, const char* a_string)
	{
		using func_t = decltype(&SetGameSettingString);
		static REL::Relocation<func_t> func{ RELOCATION_ID(73882, 75619) };
		func(a_setting, a_string);
	}

	void DescriptionPatch()
	{
		auto gameSettings = RE::GameSettingCollection::GetSingleton();
		if (!gameSettings) {
			return;
		}

		const std::vector<std::pair<const char*, const char*>> replacementRules = {
			{ "sConfirmDisenchant", "InquiryPopup" },
			{ "sEnchantmentsLearned", "SuccessPopup" }
		};

		auto settings = Settings::GetSingleton();
		for (const auto& [gameKey, jsonKey] : replacementRules) {
			const std::string& jsonString = settings->GetTranslation(jsonKey);
			if (!jsonString.empty()) {
				auto gameSetting = gameSettings->GetSetting(gameKey);
				if (gameSetting && gameSetting->GetType() == RE::Setting::Type::kString) {
					SetGameSettingString(gameSetting, jsonString.c_str());
				}
			}
		}
		
		logger::info("Description patch loaded successfully.");
	}
}
