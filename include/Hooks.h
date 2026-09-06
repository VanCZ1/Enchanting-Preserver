#pragma once

namespace Hooks
{
	void Install();

	class DisenchantHook
	{
	public:
		static void Install();
		static inline bool isDisenchanting{ false };

	private:
		static void Thunk(RE::CraftingSubMenus::EnchantConstructMenu* a_this, std::uint32_t a_unk);

		static inline REL::Relocation<decltype(Thunk)> originalFunction;
	};

	class RemoveItemHook
	{
	public:
		static void Install();

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
