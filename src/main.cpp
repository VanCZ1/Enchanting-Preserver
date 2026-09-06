#include "Log.h"
#include "Hooks.h"
#include "Translations.h"
#include "EnchantMenu.h"

namespace
{
	void Load()
	{
		Translations::GetSingleton()->Load();
		Hooks::Install();
	}

	void MessageHandler(SKSE::MessagingInterface::Message* a_msg)
	{
		switch (a_msg->type) {
		case SKSE::MessagingInterface::kDataLoaded:
			{
				EnchantMenu::DescriptionPatch();
			}
			break;
		case SKSE::MessagingInterface::kPostLoad:
			break;
		case SKSE::MessagingInterface::kPreLoadGame:
			break;
		case SKSE::MessagingInterface::kPostLoadGame:
			break;
		}
	}
}

SKSEPluginInfo(
	.Version = REL::Version{ Version::MAJOR, Version::MINOR, Version::PATCH },
	.Name = Version::PROJECT,
	.Author = Version::AUTHOR,
	.SupportEmail = ""sv,
	.StructCompatibility = SKSE::StructCompatibility::Independent,
	.RuntimeCompatibility = SKSE::VersionIndependence::AddressLibrary
)

SKSEPluginLoad(const SKSE::LoadInterface* a_skse)
{
	SKSE::Init(a_skse);

	SetupLog();
	auto plugin = SKSE::PluginDeclaration::GetSingleton();
	logger::info("{} v{}", plugin->GetName(), plugin->GetVersion());
	auto gameVersion = a_skse->RuntimeVersion().string();
	logger::info("Game version: {}", gameVersion);

	auto messaging = SKSE::GetMessagingInterface();
	if (!messaging->RegisterListener("SKSE", MessageHandler)) {
		return false;
	}
	Load();

	return true;
}
