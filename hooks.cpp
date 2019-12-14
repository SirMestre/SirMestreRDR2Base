#include "stdafx.h"

namespace hooks {
	typedef int(__fastcall* is_dlc_present_fn)(__int64 a1, DWORD dlchash);
	typedef int(__fastcall* get_player_ped_fn)(Player player);

	namespace original
	{
		get_player_ped_fn o_get_player_ped;
	}

	void main() {
		menu::Init();
	}

	int __fastcall get_player_ped_hook(Player player) {
		main();
		return original::o_get_player_ped(player);
	}

	void Init() {
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

		auto get_player_ped = memory::find_signature(0, "\x40\x53\x48\x83\xEC\x20\x33\xDB\x81\xF9", "xxxxxxxxxx");
		status = MH_CreateHook((PVOID)get_player_ped, get_player_ped_hook, reinterpret_cast<void**>(&original::o_get_player_ped));
		printf("create_status : %s\n", std::string(MH_StatusToString(status)).c_str());
		status = MH_EnableHook((PVOID)get_player_ped);
		printf("enable_status : %s\n\n", std::string(MH_StatusToString(status)).c_str());
		printf("get_player_ped: %I64X\n", get_player_ped);

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

		MH_DisableHook(get_player_ped_hook);

		MH_Uninitialize();

		Beep(220, 100);

		FreeLibraryAndExitThread(globals::hModule, 0);
	}
}