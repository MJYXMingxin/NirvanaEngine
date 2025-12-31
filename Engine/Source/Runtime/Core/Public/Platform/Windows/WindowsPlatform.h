#pragma once

#include <sal.h>
#include "Platform/GenericPlatform/GenericPlatform.h"

#if PLATFORM_COMPILER_MSVC
#include "Platform/Compiler/MSVCPlatform.h"
#elif PLATFORM_COMPILER_CLANG
#include "Platform/Compiler/ClangPlatform.h"
#endif

struct FWindowsPlatformTypes : public FGenericPlatformTypes
{
#ifdef _WIN64
	typedef unsigned __int64	SIZE_T;
	typedef __int64				SSIZE_T;
#else
	typedef unsigned long		SIZE_T;
	typedef long				SSIZE_T;
#endif
};
typedef FWindowsPlatformTypes FPlatformTypes;

#define PLATFORM_DESKTOP 1

#define DLL_EXPORT __declspec(dllexport)
#define DLL_IMPORT __declspec(dllimport)

#define PLATFORM_BREAK() (__nop(), __debugbreak())

#define USE_ALIGNED_MALLOC 1