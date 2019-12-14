#pragma once
namespace UI {
	extern void Title(const char* title);
	extern bool Option(const char* option);
	extern bool MenuOption(const char* option, const char* men);
	extern bool BoolOption(const char* option, bool *isEnabled);
	extern bool IntOption(const char* option, int *var, int min, int max, int step);
	extern bool FloatOption(const char* option, float *var, float min, float max, float step);
}