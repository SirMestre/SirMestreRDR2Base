#include "stdafx.h"

namespace controls {
	bool isMenuEnabled = false;
	bool optionpress = false;
	bool leftpress = false;
	bool rightpress = false;
	bool uppress = false;
	bool downpress = false;
	int optioncount;
	int currentoption;
	int menulevel = 0;
	int Delay = GetTickCount();

	char* currentmenu[100];
	char* actualmenu = (char*)"mainmenu";
	int lastoption[100];

	void changeMenu(const char* menuname) {
		currentmenu[menulevel] = actualmenu;
		lastoption[menulevel] = currentoption;
		menulevel++;
		actualmenu = (char*)menuname;
		currentoption = 1;
	}

	bool currentMenu(const char* menuname) {
		if (menuname == actualmenu) return true;
		else return false;
	}

	void backMenu() {
		menulevel--;
		actualmenu = currentmenu[menulevel];
		currentoption = lastoption[menulevel];
	}

	void CheckKeys() {
		optionpress = false;

		if (GetTickCount() - Delay > 100) {
			if (GetAsyncKeyState(VK_MULTIPLY)) {
				if (menulevel == 0) changeMenu("mainmenu");
				else if (menulevel == 1) backMenu();
				Delay = GetTickCount();
			}
			if (GetAsyncKeyState(VK_NUMPAD0)) {
				if (menulevel > 0)
					backMenu();
				Delay = GetTickCount();
			}
			if (GetAsyncKeyState(VK_NUMPAD5)) {
				optionpress = true;
				Delay = GetTickCount();
			}
			if (GetAsyncKeyState(VK_NUMPAD2)) {
				if (currentoption < optioncount)
					currentoption++;
				else
					currentoption = 1;
				Delay = GetTickCount();
				downpress = true;
			}
			if (GetAsyncKeyState(VK_NUMPAD8)) {
				if (currentoption > 1)
					currentoption--;
				else
					currentoption = optioncount;
				Delay = GetTickCount();
				uppress = true;
			}
			if (GetAsyncKeyState(VK_NUMPAD4)) {
				leftpress = true;
				Delay = GetTickCount();
			}
			if (GetAsyncKeyState(VK_NUMPAD6)) {
				rightpress = true;
				Delay = GetTickCount();
			}
		}
	}
}