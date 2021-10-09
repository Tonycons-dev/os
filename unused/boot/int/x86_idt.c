#ifdef __X86_64__
#include "x86_idt.h"
#include "x86_iex.h"
#include "x86_irq.h"

IDT gIDT[IDT_N_DESCRIPTORS];
IDT_PTR gIDTPtr;


void IDTSetEntry(int index, uint32 base, uint16 seg_sel, uint8 flags)
{
    IDT *this = &gIDT[index];

    this->base_low          = base & 0xFFFF;
    this->segment_selector  = seg_sel;
    this->zero              = 0;
    this->type              = flags | 0x60;
    this->base_high         = (base >> 16) & 0xFFFF;
}

void IDTSetEntries()
{
    gIDTPtr.base_address = (uint32)gIDT;
    gIDTPtr.limit = sizeof(gIDT) - 1;

    IDTSetEntry(0,  (uint32)__ISR_Exception_00, 0x08, 0x8E);
    IDTSetEntry(1,  (uint32)__ISR_Exception_01, 0x08, 0x8E);
    IDTSetEntry(2,  (uint32)__ISR_Exception_02, 0x08, 0x8E);
    IDTSetEntry(3,  (uint32)__ISR_Exception_03, 0x08, 0x8E);
    IDTSetEntry(4,  (uint32)__ISR_Exception_04, 0x08, 0x8E);
    IDTSetEntry(5,  (uint32)__ISR_Exception_05, 0x08, 0x8E);
    IDTSetEntry(6,  (uint32)__ISR_Exception_06, 0x08, 0x8E);
    IDTSetEntry(7,  (uint32)__ISR_Exception_07, 0x08, 0x8E);
    IDTSetEntry(8,  (uint32)__ISR_Exception_08, 0x08, 0x8E);
    IDTSetEntry(9,  (uint32)__ISR_Exception_09, 0x08, 0x8E);
    IDTSetEntry(10, (uint32)__ISR_Exception_10, 0x08, 0x8E);
    IDTSetEntry(11, (uint32)__ISR_Exception_11, 0x08, 0x8E);
    IDTSetEntry(12, (uint32)__ISR_Exception_12, 0x08, 0x8E);
    IDTSetEntry(13, (uint32)__ISR_Exception_13, 0x08, 0x8E);
    IDTSetEntry(14, (uint32)__ISR_Exception_14, 0x08, 0x8E);
    IDTSetEntry(15, (uint32)__ISR_Exception_15, 0x08, 0x8E);
    IDTSetEntry(16, (uint32)__ISR_Exception_16, 0x08, 0x8E);
    IDTSetEntry(17, (uint32)__ISR_Exception_17, 0x08, 0x8E);
    IDTSetEntry(18, (uint32)__ISR_Exception_18, 0x08, 0x8E);
    IDTSetEntry(19, (uint32)__ISR_Exception_19, 0x08, 0x8E);
    IDTSetEntry(20, (uint32)__ISR_Exception_20, 0x08, 0x8E);
    IDTSetEntry(21, (uint32)__ISR_Exception_21, 0x08, 0x8E);
    IDTSetEntry(22, (uint32)__ISR_Exception_22, 0x08, 0x8E);
    IDTSetEntry(23, (uint32)__ISR_Exception_23, 0x08, 0x8E);
    IDTSetEntry(24, (uint32)__ISR_Exception_24, 0x08, 0x8E);
    IDTSetEntry(25, (uint32)__ISR_Exception_25, 0x08, 0x8E);
    IDTSetEntry(26, (uint32)__ISR_Exception_26, 0x08, 0x8E);
    IDTSetEntry(27, (uint32)__ISR_Exception_27, 0x08, 0x8E);
    IDTSetEntry(28, (uint32)__ISR_Exception_28, 0x08, 0x8E);
    IDTSetEntry(29, (uint32)__ISR_Exception_29, 0x08, 0x8E);
    IDTSetEntry(30, (uint32)__ISR_Exception_30, 0x08, 0x8E);
    IDTSetEntry(31, (uint32)__ISR_Exception_31, 0x08, 0x8E);
    IDTSetEntry(32, (uint32)__IRQ_Interrupt_00, 0x08, 0x8E);
    IDTSetEntry(32, (uint32)__IRQ_Interrupt_01, 0x08, 0x8E);
    IDTSetEntry(32, (uint32)__IRQ_Interrupt_02, 0x08, 0x8E);
    IDTSetEntry(32, (uint32)__IRQ_Interrupt_03, 0x08, 0x8E);
    IDTSetEntry(32, (uint32)__IRQ_Interrupt_04, 0x08, 0x8E);
    IDTSetEntry(32, (uint32)__IRQ_Interrupt_05, 0x08, 0x8E);
    IDTSetEntry(32, (uint32)__IRQ_Interrupt_06, 0x08, 0x8E);
    IDTSetEntry(32, (uint32)__IRQ_Interrupt_07, 0x08, 0x8E);
    IDTSetEntry(32, (uint32)__IRQ_Interrupt_08, 0x08, 0x8E);
    IDTSetEntry(32, (uint32)__IRQ_Interrupt_09, 0x08, 0x8E);
    IDTSetEntry(32, (uint32)__IRQ_Interrupt_10, 0x08, 0x8E);
    IDTSetEntry(32, (uint32)__IRQ_Interrupt_11, 0x08, 0x8E);
    IDTSetEntry(32, (uint32)__IRQ_Interrupt_12, 0x08, 0x8E);
    IDTSetEntry(32, (uint32)__IRQ_Interrupt_13, 0x08, 0x8E);
    IDTSetEntry(32, (uint32)__IRQ_Interrupt_14, 0x08, 0x8E);
    IDTSetEntry(32, (uint32)__IRQ_Interrupt_15, 0x08, 0x8E);
    IDTSetEntry(128,(uint32)__ISR_Exception_128,0x08, 0x8E);

    __IDTLoad((uint32)&gIDTPtr);
    asm volatile("sti");
}

#endif