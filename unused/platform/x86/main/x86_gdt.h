#ifdef __X86_64__
#ifndef _OS_platform_X86_GDT_
#define _OS_platform_X86_GDT_

#include "constants/types.h"

#define GDT_N_DESCRIPTORS 0x08
#define GDT_KCODE_ACCESS  0x09
#define GDT_KDATA_ACCESS  0x9A
#define GDT_UCODE_ACCESS  0xFA
#define GDT_UDATA_ACCESS  0xF2
#define GDT_ENTRY_LIMIT   0xFFFFFFFF
#define GDT_GRANULARITY   0xCF

//Global descriptor table
typedef struct
{
    uint16 segment_limit;   // segment limit first 0-15 bits
    uint16 base_low;        // base first 0-15 bits
    uint8  base_middle;     // base 16-23 bits
    uint8  access;          // access byte
    uint8  granularity;     // high 4 bits (flags) low 4 bits (limit 4 last bits)(limit is 20 bit wide)
    uint8  base_high;       // base 24-31 bits
} __attribute__((packed)) GDT;

typedef struct
{
    uint16 limit;           // limit size of all GDT segments
    uint32 base_address;    // base address of the first GDT segment
} __attribute__((packed)) GDT_PTR;


extern void __asm_load_gdt(uint32 gdt_ptr);

void GDTSetEntries();
void GDTSetEntry(int index, uint32 base, uint32 limit, uint8 access, uint8 gran);

#endif
#endif