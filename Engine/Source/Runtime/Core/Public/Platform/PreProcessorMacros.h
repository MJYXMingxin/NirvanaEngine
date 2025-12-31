// Copyright MJYXMingxin, Inc. All Rights Reserved.
#pragma once

#define PROCESSOR_TO_STRING_INNER(x) #x
#define PROCESSOR_TO_STRING(x) PROCESSOR_TO_STRING_INNER(x)

#define PROCESSOR_JOIN_INNER(a, b) a##b
#define PROCESSOR_JOIN(a, b) PROCESSOR_JOIN_INNER(a, b)

#define PROCESSOR_JOIN_FIRST_INNER(a, ...) a##__VA_ARGS__
#define PROCESSOR_JOIN_FIRST(a, ...) PROCESSOR_JOIN_FIRST_INNER(a, __VA_ARGS__)

#define PROCESSOR_IF(Condition, TrueValue, FalseValue) PROCESSOR_JOIN(PROCESSOR_IF_, Condition)(TrueValue, FalseValue
#define PROCESSOR_IF_0(TrueValue, FalseValue) FalseValue
#define PROCESSOR_IF_1(TrueValue, FalseValue) TrueValue

#define COMPILED_PLATFORM_HEADER(Suffix) PROCESSOR_TO_STRING(PROCESSOR_JOIN(Platform/PLATFORM_NAME/PLATFORM_NAME, Suffix))
