#include "stdafx.h"

namespace UI {
	float menux = 330.f;
	float menuWidth = 600.f;
	float menuHeight = 580.f;
	rgba panelRectRGB = { 0, 0, 0, 80 };
	rgba titleRGB = { 255, 255, 255, 255 };
	rgba optionRectRGB{ 255, 0, 0, 200 };
	rgba optionRGB = { 255, 255, 255, 255 };
	rgba scrollerRGB = { 255, 0, 0, 255 };

	void drawRect(float x, float y, float w, float h, rgba rgba) {
		auto width = globals::resolution.right,
			height = globals::resolution.bottom;
		x /= width; w /= width;
		y /= height; h /= height;

		GRAPHICS::DRAW_RECT(x, y, w, h, rgba.r, rgba.g, rgba.b, rgba.a, 0, 0);
	}

	void drawText(std::string text, float font_size, float x, float y, rgba rgba, bool centered = false) {
		x /= globals::resolution.right; y /= globals::resolution.bottom;
		font_size /= 100.f;
		HUD::SET_TEXT_SCALE(font_size, font_size);
		HUD::_SET_TEXT_COLOR(rgba.r, rgba.g, rgba.b, rgba.a);
		HUD::SET_TEXT_CENTRE(centered);
		auto str = MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", text.c_str());
		HUD::_DRAW_TEXT(str, x, y);
	}

	void Title(const char* title) {
		controls::optioncount = 0;
		drawRect(menux, 300.f, menuWidth, menuHeight, panelRectRGB);
		drawText(title, 40.f, 300.f, 30.f, titleRGB, true);
	}

	bool Option(const char* option) {
		controls::optioncount++;

		bool thisOption = false;
		if (controls::currentoption == controls::optioncount) thisOption = true;

		if (controls::currentoption <= 16 && controls::optioncount <= 16) {
			drawText(option, 25, menux - 260.f, ((controls::optioncount * 30.f) + 40.f), optionRGB);
			if (thisOption) drawRect(menux, ((controls::optioncount * 30.22f) + 46.6f), menuWidth, 29.f, scrollerRGB);
		}

		else if ((controls::optioncount > (controls::currentoption - 16)) && controls::optioncount <= controls::currentoption)
		{
			drawText(option, 25, menux - 260.f, (((controls::optioncount - (controls::currentoption - 16)) * 30.f) + 40.f), optionRGB);
			if (thisOption) drawRect(menux, (((controls::optioncount - (controls::currentoption - 16)) * 30.22f) + 46.6f), menuWidth, 29.f, scrollerRGB);
		}

		if (controls::optionpress && controls::currentoption == controls::optioncount) return true;
		else return false;
	}

	bool MenuOption(const char* option, const char* menu) {
		Option(option);

		if (controls::optionpress && controls::currentoption == controls::optioncount) {
			controls::optionpress = false;
			controls::changeMenu(menu);
			return true;
		}
		else return false;
	}

	bool BoolOption(const char* option, bool *isEnabled) {
		Option(option);

		if (controls::currentoption <= 16 && controls::optioncount <= 16)
			drawText(*isEnabled ? "ON" : "", 25, menux + 200.f, ((controls::optioncount * 30.f) + 40.f), optionRGB);
		else if ((controls::optioncount > (controls::currentoption - 16)) && controls::optioncount <= controls::currentoption)
			drawText(*isEnabled ? "ON" : "", 25, menux + 200.f, ((controls::optioncount * 30.f) + 40.f), optionRGB);

		if (controls::optionpress && controls::currentoption == controls::optioncount) {
			*isEnabled ^= 1;
			return true;
		}
		return false;
	}

	bool IntOption(const char* option, int *var, int min, int max, int step) {
		Option(option);

		if (controls::currentoption <= 16 && controls::optioncount <= 16)
			drawText("<" + std::to_string(*var) + ">", 25, menux + 200.f, (controls::optioncount * 30.f) + 40.f, optionRGB);
		else if ((controls::optioncount > (controls::currentoption - 16)) && controls::optioncount <= controls::currentoption)
			drawText("<" + std::to_string(*var) + ">", 25, menux + 200.f, (((controls::optioncount - (controls::currentoption - 16)) * 30.f) + 40.f), optionRGB);

		if (controls::currentoption == controls::optioncount) {
			if (controls::leftpress) {
				if (*var <= min) *var = max;
				else *var -= step;
				controls::leftpress = false;
				return true;
			}
			if (*var < min) *var = max;
			if (controls::rightpress) {
				if (*var >= max) *var = min;
				else *var += step;
				controls::rightpress = false;
				return true;
			}
			if (*var > max) *var = min;
		}

		if (controls::optionpress && controls::currentoption == controls::optioncount)
			return true;
		else return false;
	}

	bool FloatOption(const char* option, float *var, float min, float max, float step) {
		Option(option);

		char buf[100];
		_snprintf_s(buf, sizeof(buf), "%.2f", *var);

		if (controls::currentoption <= 16 && controls::optioncount <= 16)
			drawText("<" + (std::string)buf + ">", 25, menux + 200.f, (controls::optioncount * 30.f) + 40.f, optionRGB);
		else if ((controls::optioncount > (controls::currentoption - 16)) && controls::optioncount <= controls::currentoption)
			drawText("<" + (std::string)buf + ">", 25, menux + 200.f, (((controls::optioncount - (controls::currentoption - 16)) * 30.f) + 40.f), optionRGB);

		if (controls::currentoption == controls::optioncount) {
			if (controls::leftpress) {
				if (*var <= min) *var = max;
				else *var -= step;
				controls::leftpress = false;
				return true;
			}
			if (*var < min) *var = max;

			if (controls::rightpress) {
				if (*var >= max) *var = min;
				else *var += step;
				controls::rightpress = false;
				return true;
			}
			if (*var > max) *var = min;
		}

		if (controls::optionpress && controls::currentoption == controls::optioncount)
			return true;
		else return false;
	}
}