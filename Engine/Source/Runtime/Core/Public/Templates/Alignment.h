#pragma once

#include "NirvanaCore.h"
#include <type_traits>

/**
 * @brief Aligns a value to the nearest higher multiple of 'Alignment', which must be a power of two.
 * @param Val			The value to align. 
 * @param Alignment		The alignment value, must be a power of two.
 * @return The value aligned up to the specified alignment.
 */
template<typename T>
_FORCE_INLINE_ constexpr T Align(T Val, uint64 Alignment)
{
	static_assert(std::is_integral_v<T> || std::is_pointer_v<T>, "Align only accepts integer or pointer type");
	return (T)(((uint64)Val + Alignment - 1) & ~(Alignment - 1));
}

/**
 * @brief Aligns a value to the nearest lower multiple of 'Alignment', which must be a power of two.
 * @param  Val			The value to align.
 * @param  Alignment	The alignment value, must be a power of two.
 * @return The value aligned down to the specified alignment.
 */
template <typename T>
_FORCE_INLINE_ constexpr T AlignDown(T Val, uint64 Alignment)
{
	static_assert(std::is_integral_v<T> || std::is_pointer_v<T>, "AlignDown only accepts integer or pointer type");

	return (T)(((uint64)Val) & ~(Alignment - 1));
}

/**
 * @brief Checks if a pointer is aligned to the specified alignment.
 * @param  Val        The value to align.
 * @param  Alignment  The alignment value, must be a power of two.
 *
 * @return true if the pointer is aligned to the specified alignment, false otherwise.
 */
template <typename T>
_FORCE_INLINE_ constexpr bool IsAligned(T Val, uint64 Alignment)
{
	static_assert(std::is_integral_v || std::is_pointer_v<T>, "IsAligned only accepts integer or pointer type");

	return !((uint64)Val & (Alignment - 1));
}

/**
 * @brief Aligns a value to the nearest higher multiple of 'Alignment'.
 * @param  Val        The value to align.
 * @param  Alignment  The alignment value, can be any arbitrary value.
 * @return The value aligned up to the specified alignment.
 */
template <typename T>
_FORCE_INLINE_ constexpr T AlignArbitrary(T Val, uint64 Alignment)
{
	static_assert(std::is_integral_v || std::is_pointer_v<T>, "AlignArbitrary only accepts integer or pointer type");

	return (T)((((uint64)Val + Alignment - 1) / Alignment) * Alignment);
}
