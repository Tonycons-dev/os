#ifndef _OS_platform_X86_PORTS_
#define _OS_platform_X86_PORTS_

#include "kernel/constants/types.h"

inline static void __writeb(uint16 port, uint8 value)
{
    asm volatile("outb %1, %0" :: "dN"(port), "a"(value));
}

inline static uint8 __readb(uint16 port)
{
    uint8 value;
    asm volatile("inb %1, %0" : "=a"(value) : "Nd"(port));
    return value;    
}

inline static void __writew(uint16 port, uint16 value)
{
    asm volatile("outw %1, %0" :: "dN"(port), "a"(value));
}

inline static uint16 __readw(uint16 port)
{
    uint16 value;
    asm volatile("inw %1, %0" : "=a"(value) : "Nd"(port));
    return value;    
}

inline static void __writel(uint16 port, uint32 value)
{
    asm volatile("outl %1, %0" :: "dN"(port), "a"(value));
}

inline static uint32 __readl(uint16 port)
{
    uint32 value;
    asm volatile("inl %1, %0" : "=a"(value) : "Nd"(port));
    return value;    
}

#endif