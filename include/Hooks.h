#pragma once

namespace Hooks
{
	void Install();

	// YesImSure skipped this function
	/*class DisenchantCallbackHook
	{
	public:
		static void InstallHook();
		static inline bool isDisenchantCallback{ false };

	private:
		static void Thunk(RE::CraftingSubMenus::EnchantConstructMenu::EnchantMenuDisenchantCallback* a_this, RE::IMessageBoxCallback::Message a_msg);
		
		static inline REL::Relocation<decltype(Thunk)> originalFunction;
	};*/

	class DisenchantHook
	{
	public:
		static void InstallHook();
		static inline bool isDisenchanting{ false };

	private:
		static void Thunk(RE::CraftingSubMenus::EnchantConstructMenu* a_this, std::uint32_t a_unk);

		static inline REL::Relocation<decltype(Thunk)> originalFunction;
	};

	class RemoveItemHook
	{
	public:
		static void InstallHook();

	private:
		static RE::ObjectRefHandle Thunk(RE::PlayerCharacter* a_this,
			RE::TESBoundObject* a_item,
			std::int32_t a_count,
			RE::ITEM_REMOVE_REASON a_reason,
			RE::ExtraDataList* a_extraList,
			RE::TESObjectREFR* a_moveToRef,
			const RE::NiPoint3* a_dropLoc,
			const RE::NiPoint3* a_rotate);

		static inline REL::Relocation<decltype(Thunk)> originalFunction;
	};
}
