#include "stdafx.h"

namespace hooks {
	typedef int(__fastcall* is_dlc_present_fn)(__int64 a1, DWORD dlchash);
	typedef int(__fastcall* get_player_ped_fn)(Player player);

	namespace original
	{
		is_dlc_present_fn o_is_dlc_present;
		get_player_ped_fn o_get_player_ped;
	}

	void main() {
		menu::Init();
	}

	int __fastcall is_dlc_present_hook(__int64 a1, DWORD dlcHash) {
		if (NETWORK::NETWORK_IS_IN_SESSION()) {
			main();
		}
		return original::o_is_dlc_present(a1, dlcHash);
	}

	int __fastcall get_player_ped_hook(Player player) {
		if (!NETWORK::NETWORK_IS_IN_SESSION()) {
			main();
		}
		return original::o_get_player_ped(player);
	}

	void initialize() {
		if (AllocConsole()) {
			freopen("CONIN$", "r", stdin);
			freopen("CONOUT$", "w", stdout);
			freopen("CONOUT$", "w", stderr);
		}

		globals::baseAddress = uintptr_t(GetModuleHandleA(0));
		auto hwnd_ = FindWindowA(0, "Red Dead Redemption 2");
		GetWindowRect(hwnd_, &globals::resolution);

		auto status = MH_Initialize();
		printf("init_status : %s\n", std::string(MH_StatusToString(status)).c_str());

		auto is_dlc_present = memory::find_signature(0, "\x81\xFA\x00\x00\x00\x00\x75\x0B\x8A", "xx????xxx") - 0x1E; // thx to @a60276468 for the sig
		printf("is_dlc_present: %I64X\n", is_dlc_present);

		status = MH_CreateHook((PVOID)is_dlc_present, is_dlc_present_hook, reinterpret_cast<void**>(&original::o_is_dlc_present));
		printf("create_status : %s\n", std::string(MH_StatusToString(status)).c_str());

		status = MH_EnableHook((PVOID)is_dlc_present);
		printf("enable_status : %s\n\n", std::string(MH_StatusToString(status)).c_str());

		auto get_player_ped = memory::find_signature(0, "\x40\x53\x48\x83\xEC\x20\x33\xDB\x81\xF9", "xxxxxxxxxx");
		status = MH_CreateHook((PVOID)get_player_ped, get_player_ped_hook, reinterpret_cast<void**>(&original::o_get_player_ped));
		printf("create_status : %s\n", std::string(MH_StatusToString(status)).c_str());
		status = MH_EnableHook((PVOID)get_player_ped);
		printf("enable_status : %s\n\n", std::string(MH_StatusToString(status)).c_str());

		Beep(220, 100);

		do {
			Sleep(100);
			if (GetAsyncKeyState(VK_INSERT) & 0x1) {
				if (controls::isMenuEnabled) {
					controls::isMenuEnabled = false;
				}
				else {
					controls::isMenuEnabled = true;
				}
			}
		} while (!(GetAsyncKeyState(VK_F12) & 0x1));

		MH_DisableHook(is_dlc_present_hook);
		MH_DisableHook(get_player_ped_hook);

		MH_Uninitialize();

		Beep(220, 100);

		FreeLibraryAndExitThread(globals::hModule, 0);
	}
}