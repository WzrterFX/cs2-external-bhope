#ifndef OFFSETS_H
#define OFFSETS_H

#include <Windows.h>

// 07.12.2023
namespace offsets
{
	// https://github.com/a2x/cs2-dumper/blob/main/generated/offsets.hpp
	const uintptr_t dwLocalPlayerPawn = 0x16C2DD8;
	const uintptr_t dwForceJump = 0x16BC240;

	// https://github.com/a2x/cs2-dumper/blob/main/generated/client.dll.hpp
	const uintptr_t m_fFlags = 0x3C8;
}

#endif