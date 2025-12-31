#pragma once
#include "Memory/MallocBase.h"

CORE_API void* LeagcyMalloc(SIZE_T Size, uint32 Alignment);
CORE_API void* LeagcyRealloc(void* Ptr, SIZE_T NewSize, uint32 Alignment);
CORE_API void LeagcyFree(void* Ptr);

class FMallocLeagcy : public FMalloc
{
public:
	FMallocLeagcy();

	//~ Begin FMalloc interface
	virtual void* Malloc(SIZE_T Count, uint32 Alignment) override;
	virtual void* TryMalloc(SIZE_T Count, uint32 Alignment) override;
	virtual void* Realloc(void* Original, SIZE_T Count, uint32 Alignment) override;
	virtual void* TryRealloc(void* Original, SIZE_T Count, uint32 Alignment) override;
	virtual void Free(void* Original) override;
	//~ End FMalloc interface
};