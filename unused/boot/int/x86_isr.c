#ifdef __X86_64__

#include "utils/kdebug.h"
#include "x86_pic8259.h"
#include "x86_isr.h"
#include "x86_idt.h"
#include "x86_iex.h"

ISRFunc gInterruptHandlers[NUM_INT_HANDLERS];

const char *cExceptionMessages[32] = 
{
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Overflow",
    "BOUND Range Exceeded",
    "Invalid Opcode",
    "Device Not Available (No Math Coprocessor)",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Invalid TSS",
    "Segment Not Present",
    "Stack-Segment Fault",
    "General Protection",
    "Page Fault",
    "Unknown Interrupt (intel reserved)",
    "x87 FPU Floating-Point Error (Math Fault)",
    "Alignment Check",
    "Machine Check",
    "SIMD Floating-Point Exception",
    "Virtualization Exception",
    "Reserved (21)",
    "Reserved (22)",
    "Reserved (23)",
    "Reserved (24)",
    "Reserved (25)",
    "Reserved (26)",
    "Reserved (27)",
    "Reserved (29)",
    "Reserved (30)",
    "Reserved (31)",
    "Reserved (128)"
};

void ISR_ExceptionHandler(X86Registers registers)
{
    if (registers.int_no < 32)
    {
        kprintf("EXCEPTION: %s\n", cExceptionMessages[registers.int_no]);
        __PrintRegisters(&registers);

        for (;;);
    }
    if (gInterruptHandlers[registers.int_no] != NULL)
    {
        ISRFunc handler = gInterruptHandlers[registers.int_no];
        handler(&registers);
    }
}

void IRQHandler(X86Registers* registers)
{
    if (gInterruptHandlers[registers->int_no] != NULL)
    {
        ISRFunc handler = gInterruptHandlers[registers->int_no];
        handler(registers);
    }

    PIC8259_EOI(registers->int_no);
}

void ISR_EndInterrupt(int num)
{
    PIC8259_EOI(num);
}

void ISR_RegisterInterruptHandler(int num, ISRFunc handler)
{
    kprintf("IRQ %d registered\n", num);

    if (num < NUM_INT_HANDLERS)
        gInterruptHandlers[num] = handler;
}

#endif