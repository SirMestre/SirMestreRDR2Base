#include "stdafx.h"

namespace menu {
	int variable_int = 0;
	float variable_float = 0.f;

	void Init() {
		controls::CheckKeys();

		if (controls::isMenuEnabled) {
			if (controls::currentMenu("mainmenu")) {
				UI::Title("SirMestre Base");
				UI::MenuOption("Self", "self");
				UI::MenuOption("Weapons", "weapons");
				UI::MenuOption("Online Players", "online");
				UI::MenuOption("Credits", "credits");
			}

			if (controls::currentMenu("self")) {
				UI::Title("Self");
				if (UI::BoolOption("God Mode", &features::isGodModeEnabled)) features::GodMode();
				if (UI::Option("Clone Ped")) features::ClonePed();
				if (UI::IntOption("Test Int", &variable_int, 0, 10, 1));
				if (UI::FloatOption("Test Float", &variable_float, 0.1f, 2.f, 0.1f));
			}

			if (controls::currentMenu("weapons")) {
				UI::Title("Weapons");
				if (UI::BoolOption("Infinite Ammo", &features::isInfiniteAmmoEnabled)) features::InfiniteAmmo();
			}

			if (controls::currentMenu("online")) {
				UI::Title("Online Players");
				for (int i = 0; i < 32; ++i) {
					if (ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i))) {
						UI::MenuOption(PLAYER::GET_PLAYER_NAME(i), "online_selected") ? features::onlineSelectedPlayer = i : NULL;
					}
				}
			}

			if (controls::currentMenu("online_selected")) {
				UI::Title(PLAYER::GET_PLAYER_NAME(features::onlineSelectedPlayer));
			}

			if (controls::currentMenu("credits")) {
				UI::Title("Credits");
				UI::Option("device9999");
				UI::Option("Revan600");
				UI::Option("Kiddion");
				UI::Option("Scriptkiddy1337");
			}
		}
	}
}
