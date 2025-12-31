#include "Memory/MallocBase.h"
#include COMPILED_PLATFORM_HEADER(PlatformMemory.h)

void* FMalloc::TryMalloc(SIZE_T Count, uint32 Alignment)
{
    return Malloc(Count, Alignment);
}

void* FMalloc::TryRealloc(void* Original, SIZE_T Count, uint32 Alignment)
{
	return Realloc(Original, Count, Alignment);
}

void* FMalloc::MallocZeroed(SIZE_T Count, uint32 Alignment)
{
	void* const Memory = Malloc(Count, Alignment);
	if (Memory)
	{
		FPlatformMemory::Memzero(Memory, Count);
	}
	return Memory;
}

void* FMalloc::TryMallocZeroed(SIZE_T Count, uint32 Alignment)
{
	return MallocZeroed(Count, Alignment);
}
