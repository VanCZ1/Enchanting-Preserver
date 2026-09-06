#include "EnchantMenu.h"
#include "Translations.h"
#include "Offsets.h"

namespace EnchantMenu
{
	void DescriptionPatch()
	{
		const auto gameSettings = RE::GameSettingCollection::GetSingleton();
		if (!gameSettings) {
			return;
		}

		constexpr std::array<std::pair<std::string_view, std::string_view>, 2> replacementRules{{ 
			{ "sConfirmDisenchant", "InquiryPopup" },
			{ "sEnchantmentsLearned", "SuccessPopup" }
		}};

		for (const auto& [gameKey, transKey] : replacementRules) {
			const auto transStr = Trans(transKey);
			if (!transStr || *transStr == '\0') {
				continue;
			}

			const auto gameSetting = gameSettings->GetSetting(gameKey.data());
			if (gameSetting && gameSetting->GetType() == RE::Setting::Type::kString) {
				Offsets::SetGameSettingString(gameSetting, transStr);
			}
		}
	}
}
