#include "stdafx.h"

namespace features {
	int onlineSelectedPlayer = 0;

	bool isGodModeEnabled = false;
	bool isInfiniteAmmoEnabled = false;

	void GodMode() {
		ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::PLAYER_PED_ID(), isGodModeEnabled);
	}

	void ClonePed() {
		PED::CLONE_PED(PLAYER::PLAYER_PED_ID(), ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), 0, 1);
	}

	void InfiniteAmmo() {
		WEAPON::SET_PED_INFINITE_AMMO(PLAYER::PLAYER_PED_ID(), isInfiniteAmmoEnabled, 0);
	}
}
