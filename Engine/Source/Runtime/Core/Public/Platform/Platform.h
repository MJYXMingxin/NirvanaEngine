// Copyright MJYXMingxin, Inc. All Rights Reserved.
#pragma once

//Windows platform detection
#if defined(_WIN32) || defined(_WIN64)
#	define PLATFORM_WINDOWS 1
#	define PLATFORM_NAME Windows
#else
#	define PLATFORM_WINDOWS 0
#endif

// Linux platform detection
#if defined(__linux__)
#	define PLATFORM_LINUX 1
#	define PLATFORM_NAME Linux
#else
#	define PLATFORM_LINUX 0
#endif

// macOS platform detection
#if defined(__APPLE__) && defined(__MACH__)
#	define PLATFORM_MAC 1
#	define PLATFORM_NAME Mac
#else
#	define PLATFORM_MAC 0
#endif

#if defined(_WIN64) || defined(__LP64__) || defined(__x86_64__) || defined(__aarch64__)
#   define PLATFORM_64BITS 1
#else
#	define PLATFORM_64BITS 0
#endif

#if defined(__clang__) && !defined(_MSC_VER)
#   define PLATFORM_COMPILER_CLANG 1
#	define PLATFORM_COMPILER_MSVC 0
#	define COMPILER_VERSION (__clang_major__ * 100 + __clang_minor__)
#	define COMPILER_NAME "Clang"
#elif defined(_MSC_VER)
#   define PLATFORM_COMPILER_CLANG 0
#	define PLATFORM_COMPILER_MSVC 1
#	define COMPILER_VERSION _MSC_VER
#	define COMPILER_NAME "MSVC"
#else
#   error "Unsupported compiler!"
#endif

#include "PreProcessorMacros.h"
#include "GenericPlatform/GenericPlatform.h"

#include COMPILED_PLATFORM_HEADER(Platform.h)

//~ Unsigned base types.
typedef FPlatformTypes::uint8 uint8;
typedef FPlatformTypes::uint16 uint16;
typedef FPlatformTypes::uint32 uint32;
typedef FPlatformTypes::uint64 uint64;

//~ Signed base types.
typedef FPlatformTypes::int8 int8;
typedef FPlatformTypes::int16 int16;
typedef FPlatformTypes::int32 int32;
typedef FPlatformTypes::int64 int64;

//~ Character types.
typedef FPlatformTypes::AnsiChar AnsiChar;
typedef FPlatformTypes::WideChar WideChar;
typedef FPlatformTypes::TChar TChar;
typedef FPlatformTypes::UTF8Char UTF8Char;
typedef FPlatformTypes::char16 UCS2CHAR;
typedef FPlatformTypes::char16 UTF16Char;
typedef FPlatformTypes::char32 UTF32Char;

typedef FPlatformTypes::UPTRINT UPTRINT;
typedef FPlatformTypes::PTRINT PTRINT;
typedef FPlatformTypes::SIZE_T SIZE_T;
typedef FPlatformTypes::SSIZE_T SSIZE_T;

typedef FPlatformTypes::TYPE_OF_NULL TYPE_OF_NULL;
typedef FPlatformTypes::TYPE_OF_NULLPTR TYPE_OF_NULLPTR;

#define UTF8_TEXT(x) u8##x
#define UTF16_TEXT(x) u##x
#define WIDE_TEXT(x) L##x
#define _TEXT(x) WIDE_TEXT(x)