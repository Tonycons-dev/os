#ifdef __X86_64__
#include "x86_pic8259.h"
#include "platform/x86/io/x86Ports.h"

void PIC8259_Init()
{
    unsigned char a1, a2;

    a1 = __readb(PIC1_DATA);
    a2 = __readb(PIC2_DATA);

    __writeb(PIC1_COMMAND, ICW1);
    __writeb(PIC2_COMMAND, ICW1);

    __writeb(PIC1_DATA, 0x20);
    __writeb(PIC2_DATA, 0x28);

    __writeb(PIC1_DATA, ICW4_8086);
    __writeb(PIC2_DATA, ICW4_8086);

    __writeb(PIC1_DATA, a1);
    __writeb(PIC2_DATA, a2);
}

void PIC8259_EOI(unsigned char irq)
{
    if (irq >= 0x28)
        __writeb(PIC2_ADDRESS, PIC_EOI);

    __writeb(PIC1_ADDRESS, PIC_EOI);
}

#endif