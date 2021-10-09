#ifndef _OS_ARCH_I386_TYPES_
#define _OS_ARCH_I386_TYPES_

#include <stdint.h>
#include <stddef.h>

typedef uint8_t uint8;
typedef int8_t int8;
typedef uint16_t uint16;
typedef int16_t int16;
typedef uint32_t uint32;
typedef int32_t int32;
typedef uint64_t uint64;
typedef int64_t int64;
typedef uintptr_t uintptr;
typedef intptr_t intptr;

#ifndef __cplusplus
_Static_assert(sizeof(uint8) == 1, "Error: i386: uint8 must be 1 byte");
_Static_assert(sizeof(int8) == 1, "Error: i386: int8 must be 1 byte");
_Static_assert(sizeof(uint16) == 2, "Error: i386: uint16 must be 2 bytes");
_Static_assert(sizeof(int16) == 2, "Error: i386: int16 must be 2 bytes");
_Static_assert(sizeof(uint32) == 4, "Error: i386: uint32 must be 4 bytes");
_Static_assert(sizeof(int32) == 4, "Error: i386: int32 must be 4 bytes");
_Static_assert(sizeof(void*) == 4, "Error: i386: Incorrect address size. (Must be 4 bytes).");
_Static_assert(sizeof(uintptr_t) == sizeof(void*), "i386: sizeof(uintptr_t) is not equal to sizeof(void*)");
#else
static_assert(sizeof(uint8) == 1, "Error: i386: uint8 must be 1 byte");
static_assert(sizeof(int8) == 1, "Error: i386: int8 must be 1 byte");
static_assert(sizeof(uint16) == 2, "Error: i386: uint16 must be 2 bytes");
static_assert(sizeof(int16) == 2, "Error: i386: int16 must be 2 bytes");
static_assert(sizeof(uint32) == 4, "Error: i386: uint32 must be 4 bytes");
static_assert(sizeof(int32) == 4, "Error: i386: int32 must be 4 bytes");
static_assert(sizeof(void*) == 4, "Error: i386: Incorrect address size. (Must be 4 bytes).");
static_assert(sizeof(uintptr_t) == sizeof(void*), "i386: sizeof(uintptr_t) is not equal to sizeof(void*)");
#endif

#endif