#pragma once

#include "NirvanaCore.h"

enum
{
	DEFAULT_ALIGNMENT = 0,
	MIN_ALIGNMENT = 8
};

CORE_API extern class FMalloc* GMalloc;

class FMalloc
{
public:

	/**
	 * @brief Allocate memory
	 * @param Count			Target memory count
	 * @param Alignment		Targetmemory alignment
	 * @return Allocated memory
	 */
	virtual void* Malloc(SIZE_T Count, uint32 Alignment = DEFAULT_ALIGNMENT) = 0;

	/**
	 * @brief Try to allocate memory
	 * @note This function will call Malloc(), sometimes it may return nullptr
	 *		 if the allocation request cannot be satisfied.
	 * @param Count			Target memory count
	 * @param Alignment		Targetmemory alignment
	 * @return Allocated memory
	 * @see Malloc()
	 */
	CORE_API virtual void* TryMalloc(SIZE_T Count, uint32 Alignment = DEFAULT_ALIGNMENT);

	/**
	 * @brief Reallocate memory
	 * @param Original		The origin memory
	 * @param Count			Target memory count
	 * @param Alignment		Target memory alignment
	 * @return Reallocated memory
	 */
	virtual void* Realloc(void* Original, SIZE_T Count, uint32 Alignment = DEFAULT_ALIGNMENT) = 0;

	/**
	 * @brief Try to reallocate memory
	 * @note This function will call Realloc(), sometimes it may return nullptr
	 *		 if the allocation request cannot be satisfied.
	 * @param Original		The origin memory
	 * @param Count			Target memory count
	 * @param Alignment		Target memory alignment
	 * @return Reallocated memory
	 * @see Realloc()
	 */
	CORE_API virtual void* TryRealloc(void* Original, SIZE_T Count, uint32 Alignment = DEFAULT_ALIGNMENT);

	/**
	 * @brief Free memory
	 * @param Original		Target memory to free
	 */
	virtual void Free(void* Original) = 0;

	/**
	 * @brief Allocate zeroed memory
	 * @param Count			Target memory count
	 * @param Alignment		Target memory alignment
	 * @return Allocate memory
	 */
	CORE_API virtual void* MallocZeroed(SIZE_T Count, uint32 Alignment = DEFAULT_ALIGNMENT);

	/**
	 * @brief Try to allocate zeroed memory
	 * @note This function will call MallocZeroed(), sometimes it may return nullptr
	 *		 if the allocation request cannot be satisfied.
	 * @param Count			Target memory count
	 * @param Alignment		Target memory alignment
	 * @return Allocate memory
	 * @see MallocZeroed()
	 */
	CORE_API virtual void* TryMallocZeroed(SIZE_T Count, uint32 Alignment = DEFAULT_ALIGNMENT);

	/**
	 * @brief Get the name of this allocator
	 */
	virtual const TChar* GetAllocatorName()
	{
		return _TEXT("Undefined allocator");
	}

};