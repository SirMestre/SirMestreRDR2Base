#pragma once
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <windows.h>
#include <stdio.h>
#include <string>
#include <Psapi.h>
#include <map>

#include "MinHook/MinHook.h"
#pragma comment(lib, "MinHook/libMinHook.x64.lib")

#include "crossmap.h"
#include "invoker.h"
#include "natives.h"
#include "globals.h"
#include "hooks.h"
#include "memory.h"
#include "controls.h"
#include "UI.h"
#include "menu.h"
#include "features.h"

struct rgba {
	int r, g, b, a;
};