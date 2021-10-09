#ifdef __X86_64__
#include "x86_gdt.h"

GDT gGDT[GDT_N_DESCRIPTORS];
GDT_PTR gGDTPtr;

void GDTSetEntry(int index, uint32 base, uint32 limit, uint8 access, uint8 gran)
{
    GDT *this = &gGDT[index];

    this->segment_limit = limit & 0xFFFF;
    this->base_low      = base & 0xFFFF;
    this->base_middle   = (base >> 16) & 0xFF;
    this->access        = access;
    this->granularity   = (limit >> 16) & 0x0F;
    this->granularity   = this->granularity | (gran & 0xF0);
    this->base_high     = (base >> 24 & 0xFF);
}

void GDTSetEntries()
{
    gGDTPtr.limit = sizeof(gGDT) - 1;
    gGDTPtr.base_address = (uint32)gGDT;

    GDTSetEntry(0, 0U, 0x00000000U, 0x00, 0x00);

    GDTSetEntry(1, 0U, 0xFFFFFFFFU, GDT_KCODE_ACCESS, GDT_GRANULARITY);
    GDTSetEntry(2, 0U, 0xFFFFFFFFU, GDT_KDATA_ACCESS, GDT_GRANULARITY);
    GDTSetEntry(3, 0U, 0xFFFFFFFFU, GDT_UCODE_ACCESS, GDT_GRANULARITY);
    GDTSetEntry(4, 0U, 0xFFFFFFFFU, GDT_UDATA_ACCESS, GDT_GRANULARITY);

    __GDTLoad((uint32)&gGDTPtr);
}

#endif