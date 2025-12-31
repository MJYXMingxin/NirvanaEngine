#include "Platform/GenericPlatform/GenericPlatformMemory.h"
#include "Memory/MemoryBase.h"

FMalloc* FGenericPlatformMemory::BaseMalloc()
{
	static FMalloc* Instance = nullptr;
	if (Instance != nullptr)
	{
		return Instance;
	}
	
    return nullptr;
}
