#pragma once

#include "NirvanaCore.h"
#include <string.h>
#include <wchar.h>

class FMalloc;

class FGenericPlatformMemory
{
public:
	static CORE_API FMalloc* BaseMalloc();

	static _FORCE_INLINE_ void* Memmove(void* Dest, const void* Src, SIZE_T Count)
	{
		return memmove(Dest, Src, Count);
	}

	static _FORCE_INLINE_ int32 Memcmp(const void* Buf1, const void* Buf2, SIZE_T Count)
	{
		return memcmp(Buf1, Buf2, Count);
	}

	static _FORCE_INLINE_ void* Memset(void* Dest, uint8 Char, SIZE_T Count)
	{
		return memset(Dest, Char, Count);
	}

	static _FORCE_INLINE_ void* Memzero(void* Dest, SIZE_T Count)
	{
		return memset(Dest, 0, Count);
	}

	static _FORCE_INLINE_ void* Memcpy(void* Dest, const void* Src, SIZE_T Count)
	{
		return memcpy(Dest, Src, Count);
	}
};