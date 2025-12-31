// Copyright MJYXMingxin, Inc. All Rights Reserved.
#pragma once

template<typename T32BITS, typename T64BITS, int PointerSize>
struct TSelectIntPointerType
{
};

template<typename T32BITS, typename T64BITS>
struct TSelectIntPointerType<T32BITS, T64BITS, 8>
{
	typedef T64BITS TIntPointer;
};

template<typename T32BITS, typename T64BITS>
struct TSelectIntPointerType<T32BITS, T64BITS, 4>
{
	typedef T32BITS TIntPointer;
};

struct FGenericPlatformTypes
{
	typedef unsigned char		uint8;
	typedef unsigned short		uint16;
	typedef unsigned int		uint32;
	typedef unsigned long long	uint64;
	typedef signed char			int8;
	typedef signed short		int16;
	typedef signed int			int32;
	typedef signed long long	int64;

	typedef char				AnsiChar;
	typedef wchar_t				WideChar;
	typedef char8_t				char8;
	typedef char16_t			char16;
	typedef char32_t			char32;
	typedef WideChar			TChar;
	typedef char8				UTF8Char;

	typedef TSelectIntPointerType<uint32, uint64, sizeof(void*)>::TIntPointer UPTRINT;
	typedef TSelectIntPointerType<int32, int64, sizeof(void*)>::TIntPointer PTRINT;

	typedef UPTRINT SIZE_T;
	typedef PTRINT SSIZE_T;

	typedef int32					TYPE_OF_NULL;
	typedef decltype(nullptr)		TYPE_OF_NULLPTR;
};
