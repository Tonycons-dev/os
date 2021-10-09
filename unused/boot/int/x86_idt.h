#ifdef __X86_64__
#ifndef _OS_platform_X86_IDT_
#define _OS_platform_X86_IDT_

#define IDT_N_DESCRIPTORS     0xFF

//Interrupt descriptor table
typedef struct _IDT
{
    uint16 base_low;            // lower 16 bits 0-15 of the address to jump to when this interrupt fires
    uint16 segment_selector;    // code segment selector in GDT
    uint8  zero;                // unused, always be zero
    uint8  type;                // types trap, interrupt gates
    uint16 base_high;           // upper 16 bits 16-31 of the address to jump to
} __attribute__((packed)) IDT;

typedef struct _IDT_PTR
{
    uint16 limit;               // limit size of all IDT segments
    uint32 base_address;        // base address of the first IDT segment
} __attribute__((packed)) IDT_PTR;


void IDTSetEntry(int index, uint32 base, uint16 seg_sel, uint8 flags);
void IDTSetEntries();

extern void __IDTLoad(uint32 idtAddress);

#endif
#endif