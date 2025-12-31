#pragma once

#define _FORCE_INLINE_ inline __attribute__((always_inline))
#define _NO_INLINE_ __attribute__((noinline))
#define _ALIGNED(x) __attribute__((aligned(x)))