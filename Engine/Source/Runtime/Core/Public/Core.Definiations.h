// Copyright MJYXMingxin, Inc. All Rights Reserved.
#pragma once

// Platform-specific export/import macros
#if defined(_WIN32) || defined(_WIN64)
#	if defined(NIRVANA_CORE_EXPORTS)
// Building the Core DLL - export symbols
#		define CORE_API DLL_EXPORT
#	else
// Using the Core DLL - import symbols
#		define CORE_API DLL_IMPORT
#	endif
#else
// On other platforms (Linux, macOS), use visibility attributes
#	define CORE_API __attribute__((visibility("default")))
#endif