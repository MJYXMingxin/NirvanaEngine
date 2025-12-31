#include "Memory/MallocLeagcy.h"
#include "Templates/Alignment.h"
#if PLATFORM_WINDOWS
#include <Windows.h>
#endif

void* LeagcyMalloc(SIZE_T Size, uint32 Alignment)
{
#if USE_ALIGNED_MALLOC
	void* Result = _aligned_malloc(Size, Alignment);
#else
	void* Ptr = malloc(Size + Alignment + sizeof(void*) + sizeof(SIZE_T));
	void* Result = nullptr;
	if (Ptr)
	{
		Result = Align((uint8*)Ptr + sizeof(void*) + sizeof(SIZE_T), Alignment);
		*((void**)((uint8*)Result - sizeof(void*))) = Ptr;
		*((SIZE_T*)((uint8*)Result - sizeof(void*) - sizeof(SIZE_T))) = Size;
	}
#endif
	return Result;
}

static SIZE_T LeagcyGetAllocationSize(void* Original)
{
#if USE_ALIGNED_MALLOC
	return _aligned_msize(Original, 16, 0)
#else
	return *((SIZE_T*)((uint8*)Original - sizeof(void*) - sizeof(SIZE_T)));
#endif
}

void* LeagcyRealloc(void* Ptr, SIZE_T NewSize, uint32 Alignment)
{

}

void LeagcyFree(void* Ptr)
{
}

FMallocLeagcy::FMallocLeagcy()
{
#if PLATFORM_WINDOWS
	// Enable low fragmentation heap - http://msdn2.microsoft.com/en-US/library/aa366750.aspx
	intptr_t	CrtHeapHandle = _get_heap_handle();
	ULONG		EnableLFH = 2;
	HeapSetInformation((void*)CrtHeapHandle, HeapCompatibilityInformation, &EnableLFH, sizeof(EnableLFH));
#endif
}

void* FMallocLeagcy::Malloc(SIZE_T Count, uint32 Alignment)
{
	return nullptr;
}

void* FMallocLeagcy::TryMalloc(SIZE_T Count, uint32 Alignment)
{
	return nullptr;
}

void* FMallocLeagcy::Realloc(void* Original, SIZE_T Count, uint32 Alignment)
{
	return nullptr;
}

void* FMallocLeagcy::TryRealloc(void* Original, SIZE_T Count, uint32 Alignment)
{
	return nullptr;
}

void FMallocLeagcy::Free(void* Original)
{
}
