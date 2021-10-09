#ifdef __X86_64__
#ifndef _OS_platform_X86_ISR_
#define _OS_platform_X86_ISR_

#include "platform/x86/registers/x86_registers.h"

#define NUM_INT_HANDLERS    0xFF

typedef void (*ISRFunc)(X86Registers*);

void ISRRegisterInterruptHandler(int inum, ISRFunc handler);
void ISREndInterrupt(int inum);

#endif
#endif