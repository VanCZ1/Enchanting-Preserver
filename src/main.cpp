#include "Log.h"
#include "Hooks.h"
#include "Settings.h"
#include "EnchantMenu.h"

SKSEPluginInfo(
	.Version = REL::Version{ Version::MAJOR, Version::MINOR, Version::PATCH },
	.Name = Version::PROJECT,
	.Author = Version::AUTHOR,
	.SupportEmail = ""sv,
	.StructCompatibility = SKSE::StructCompatibility::Independent,
	.RuntimeCompatibility = SKSE::VersionIndependence::AddressLibrary
)

void MessageHandler(SKSE::MessagingInterface::Message* a_msg)
{
	switch (a_msg->type) {
	case SKSE::MessagingInterface::kDataLoaded:

		EnchantMenu::DescriptionPatch();

		break;
	case SKSE::MessagingInterface::kPostLoad:
		break;
	case SKSE::MessagingInterface::kPreLoadGame:
		break;
	case SKSE::MessagingInterface::kPostLoadGame:
		break;
	case SKSE::MessagingInterface::kNewGame:
		break;
	}
}

SKSEPluginLoad(const SKSE::LoadInterface* skse)
{
	SKSE::Init(skse);

	SetupLog();

	auto plugin = SKSE::PluginDeclaration::GetSingleton();
	logger::info("{} v{}", plugin->GetName(), plugin->GetVersion());
	auto gameVersion = skse->RuntimeVersion().string();
	logger::info("Game version: {}", gameVersion);

	Settings::GetSingleton()->LoadTranslation();
	Hooks::Install();

	auto messaging = SKSE::GetMessagingInterface();
	if (!messaging->RegisterListener("SKSE", MessageHandler)) {
		return false;
	}

	logger::info("Plugin loaded successfully.");

	return true;
}
