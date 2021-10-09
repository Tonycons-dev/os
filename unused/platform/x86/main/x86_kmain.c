#ifdef __X86_64__

#include "x86_kmain.h"
#include "x86_gdt.h"
#include "platform/x86/int/x86_isr.h"
#include "platform/x86/int/x86_idt.h"
#include "platform/x86/input/x86KeyboardHandler.h"
#include "platform/x86/input/x86MouseHandler.h"


void kmain(void)
{
    GDTSetEntries();
    IDTSetEntries();

    RegisterISRInterruptHandlers();

    KeyboardInit();
    MouseInit();
}

#endif