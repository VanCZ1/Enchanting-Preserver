#pragma once

namespace Offsets
{
	inline void SetGameSettingString(RE::Setting* a_this, const char* a_str)
	{
		using func_t = decltype(&SetGameSettingString);
		static REL::Relocation<func_t> func{ RELOCATION_ID(73882, 75619) };
		func(a_this, a_str);
	}
}
