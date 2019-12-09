#pragma once
#include "stdafx.h"

typedef DWORD Void;
typedef DWORD Any;
typedef DWORD uint;
typedef DWORD Hash;
typedef int Entity;
typedef int Player;
typedef int FireId;
typedef int Ped;
typedef int Vehicle;
typedef int Cam;
typedef int CarGenerator;
typedef int Group;
typedef int Train;
typedef int Pickup;
typedef int Object;
typedef int Weapon;
typedef int Interior;
typedef int Blip;
typedef int Texture;
typedef int TextureDict;
typedef int CoverPoint;
typedef int Camera;
typedef int TaskSequence;
typedef int ColourIndex;
typedef int Sphere;
typedef int INT, ScrHandle;
struct Vector3
{
	float x;
	float y;
	float z;
};

class Context // credits to rdr2 ScriptHook
{
	// Internal RAGE stuff
	uint64_t* retVal = stack;
	uint64_t argCount = 0;
	uint64_t* stackPtr = stack;
	uint64_t dataCount = 0;
	uint64_t spaceForResults[24];
	// Our stack
	uint64_t stack[24]{ 0 };

public:
	template<class T>
	T& At(uint32_t idx) {
		static_assert(sizeof(T) <= 8, "Argument is too big");

		return *reinterpret_cast<T*>(stack + idx);
	}

	uint32_t GetArgsCount() {
		return argCount;
	}

	void SetArgsCount(uint32_t idx) {
		argCount = idx;
	}

	template<class T, class... Args>
	void Push(T arg, Args... args) {
		static_assert(sizeof(T) <= 8, "Argument is too big");

		*(T*)(stack + argCount++) = arg;

		if constexpr (sizeof...(Args) > 0)
			Push(args...);
	}

	template<class T>
	T Result() {
		return *reinterpret_cast<T*>(retVal);
	}
	template<>
	void Result<void>() { }

	template<>
	Vector3 Result<Vector3>() {
		Vector3 vec;
		vec.x = *(float*)((uintptr_t)retVal + 0);
		vec.y = *(float*)((uintptr_t)retVal + 8);
		vec.z = *(float*)((uintptr_t)retVal + 16);
		return vec;
	}

	void Reset() {
		argCount = 0;
		dataCount = 0;
	}

	void CopyResults() {
		uint64_t a1 = (uint64_t)this;

		uint64_t result;

		for (; *(uint32_t*)(a1 + 24); *(uint32_t*)(*(uint64_t*)(a1 + 8i64 * *(signed int*)(a1 + 24) + 32) + 16i64) = result)
		{
			--* (uint32_t*)(a1 + 24);
			**(uint32_t * *)(a1 + 8i64 * *(signed int*)(a1 + 24) + 32) = *(uint32_t*)(a1 + 16 * (*(signed int*)(a1 + 24) + 4i64));
			*(uint32_t*)(*(uint64_t*)(a1 + 8i64 * *(signed int*)(a1 + 24) + 32) + 8i64) = *(uint32_t*)(a1
				+ 16i64
				* *(signed int*)(a1 + 24)
				+ 68);
			result = *(unsigned int*)(a1 + 16i64 * *(signed int*)(a1 + 24) + 72);
		}
		-- * (uint32_t*)(a1 + 24);
	}
};

typedef void(__cdecl * Handler)(Context * context);
template<class Retn = uint64_t, class... Args>
static Retn invoke_(Handler fn, Args... args)
{
	static Context ctx;

	if (!fn) return Retn();

	ctx.Reset();

	if constexpr (sizeof...(Args) > 0)
		ctx.Push(args...);

	__try {
		fn(&ctx);
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
	}
	__try {
		ctx.CopyResults();
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
	}

	return ctx.Result<Retn>();
}

static Handler get_handler(uintptr_t hash_) {
	static auto base_address = (uintptr_t)GetModuleHandleA(0);
	auto it = nativehash_to_address_table.find(hash_);
	if (it != nativehash_to_address_table.end()) {
		if (it->first == hash_)
			return (Handler)(base_address + it->second);
	}
	return 0;
}

template<class Retn = uint64_t, class... Args>
static Retn invoke(uint64_t hashName, Args... args) {
	return invoke_<Retn>(get_handler(hashName), args...);
}