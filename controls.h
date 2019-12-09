#pragma once
namespace controls {
	extern bool isMenuEnabled;
	extern int optioncount;
	extern int currentoption;
	extern bool optionpress;
	extern bool leftpress;
	extern bool rightpress;
	extern bool uppress;
	extern bool downpress;
	extern void CheckKeys();
	extern bool currentMenu(const char* menuname);
	extern void changeMenu(const char* menuname);
}