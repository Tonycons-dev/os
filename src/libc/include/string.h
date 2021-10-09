#ifndef _TERRA_LIBC_STRING_
#define _TERRA_LIBC_STRING_ 1
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>

void* memset(void* destination, char fill, size_t numBytes);
void* memcpy(void* destination, const void* source, size_t numBytes);
void* memmove(void* destination, const void* source, size_t numBytes);

int memcmp(uint8_t* source1, uint8_t* source2, size_t num);
int strlen(const char* string);
int strcmp(const char* first, const char* second);
int strcpy(char* destination, const char* source);
int isspace(char c);

void itoa(char* buf, int base, int d);

#ifdef __cplusplus
}
#endif
#endif