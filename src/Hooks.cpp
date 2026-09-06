#include "Hooks.h"

namespace Hooks
{
	void Install()
	{
		logger::info("Installing hooks...");
		SKSE::AllocTrampoline(14);
		DisenchantHook::Install();
		RemoveItemHook::Install();
		logger::info("Hooks installed successfully.");
	}

	void DisenchantHook::Install()
	{
		// In the disenchant function of EnchantConstructMenu
		// 1.5.97: sub_14086D830 call sub_14086DB70
		// 1.6.1170: sub_14090BD60 call sub_14090BF80
		REL::Relocation<std::uintptr_t> target{ RELOCATION_ID(50459, 51363), REL::VariantOffset(0xC8, 0xC8, 0xC8) };
		auto& trampoline = SKSE::GetTrampoline();
		originalFunction = trampoline.write_call<5>(target.address(), Thunk);
	}

	void DisenchantHook::Thunk(RE::CraftingSubMenus::EnchantConstructMenu* a_this, std::uint32_t a_unk)
	{
		isDisenchanting = true;
		originalFunction(a_this, a_unk);
	}

	void RemoveItemHook::Install()
	{
		REL::Relocation<std::uintptr_t> vTable{ RE::PlayerCharacter::VTABLE[0] };
		originalFunction = vTable.write_vfunc(0x56, Thunk);
	}

	RE::ObjectRefHandle RemoveItemHook::Thunk(RE::PlayerCharacter* a_this,
		RE::TESBoundObject* a_item,
		std::int32_t a_count,
		RE::ITEM_REMOVE_REASON a_reason,
		RE::ExtraDataList* a_extraList,
		RE::TESObjectREFR* a_moveToRef,
		const RE::NiPoint3* a_dropLoc,
		const RE::NiPoint3* a_rotate)
	{
		if (DisenchantHook::isDisenchanting) {
			DisenchantHook::isDisenchanting = false;
			if (a_item && (a_item->IsArmor() || a_item->IsWeapon())) {
				a_count = 0;
			}
		}

		return originalFunction(a_this, a_item, a_count, a_reason, a_extraList, a_moveToRef, a_dropLoc, a_rotate);
	}
}
