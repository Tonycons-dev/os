#include "libc/include/string.h"


void* memset(void* destination, char fill, size_t numBytes)
{
    char* temp = (char*)destination;

    for (; numBytes != 0; numBytes--)
        *temp++ = fill;
    
    return destination;
}

void* memcpy(void* destination, const void* source, size_t numBytes)
{
    char* p = destination;
    const char* q = source;

    while (numBytes--)
        *p++ = *q++;

    return destination;
}

int memcmp(uint8_t* first, uint8_t* second, size_t num)
{
    uint8_t* p = first;
    uint8_t* q = second;

    while (num--)
    {   
        if (*p != *q)
            return 0;

        ++p;
        ++q;
    }
    return 1;
}

int strlen(const char* str)
{
    int length = 0;
    const char* s = str;

    while (*s++)
        length++;

    return length;
}

int strcmp(const char* first, const char* second)
{
    int index = 0;

    while ((first[index] == second[index])) 
    {
        if (second[index++] == 0)
            return 0;
    }
    return 1;
}

int strcpy(char *destination, const char *source) 
{
    int i = 0;

    while ((*destination++ = *source++) != 0)
        i++;

    return i;
}

void strcat(char *destination, const char *source) 
{
    char *end = (char*)destination + strlen(destination);

    memcpy((void*)end, (void*)source, strlen(source));

    end = end + strlen(source);
    *end = '\0';
}

int isspace(char c) 
{
    return c == ' ' || c == '\t' || c == '\n' || 
        c == '\v' || c == '\f' || c == '\r';
}

void itoa(char *buf, int base, int d) 
{
    char *p = buf;
    char *p1, *p2;
    unsigned long ud = d;
    int divisor = 10;

    if (base == 'd' && d < 0) 
    {
        *p++ = '-';
        buf++;
        ud = -d;
    } 
    else if (base == 'x')
        divisor = 16;

    do {
        int remainder = ud % divisor;
        *p++ = (remainder < 10) ? remainder + '0' : remainder + 'a' - 10;
    } while (ud /= divisor);

    *p = 0;
    p1 = buf;
    p2 = p - 1;

    while (p1 < p2) 
    {
        char tmp = *p1;
        *p1 = *p2;
        *p2 = tmp;
        p1++;
        p2--;
    }
}