#ifdef __X86_64__
#ifndef _OS_platform_X86_IEX_
#define _OS_platform_X86_IEX_

#include "platform/x86/registers/x86_registers.h"

//X86 ISR Exceptions

void ISR_ExceptionHandler(X86Registers registers);

extern void __ISR_Exception_00(); //Division By Zero
extern void __ISR_Exception_01(); //Debug
extern void __ISR_Exception_02(); //Non Maskable Interrupt
extern void __ISR_Exception_03(); //Breakpoint
extern void __ISR_Exception_04(); //Overflow
extern void __ISR_Exception_05(); //BOUND Range Exceeded
extern void __ISR_Exception_06(); //Invalid Opcode
extern void __ISR_Exception_07(); //Device Not Available
extern void __ISR_Exception_08(); //Double Fault
extern void __ISR_Exception_09(); //Coprocessor Segment Overrun
extern void __ISR_Exception_10(); //Invalid TSS
extern void __ISR_Exception_11(); //Segment Not Present
extern void __ISR_Exception_12(); //Stack-Segment Fault
extern void __ISR_Exception_13(); //General Protection
extern void __ISR_Exception_14(); //Page Fault
extern void __ISR_Exception_15(); //Unknown Interrupt (Intel Reserved)
extern void __ISR_Exception_16(); //X87 FPU Floating-Point Error
extern void __ISR_Exception_17(); //Alignment Check
extern void __ISR_Exception_18(); //Machine Check
extern void __ISR_Exception_19(); //SIMD Floating-Point Exception
extern void __ISR_Exception_20(); //Virtualization Exception
extern void __ISR_Exception_21(); //Reserved (21)
extern void __ISR_Exception_22(); //Reserved (22)
extern void __ISR_Exception_23(); //Reserved (23)
extern void __ISR_Exception_24(); //Reserved (24)
extern void __ISR_Exception_25(); //Reserved (25)
extern void __ISR_Exception_26(); //Reserved (26)
extern void __ISR_Exception_27(); //Reserved (27)
extern void __ISR_Exception_28(); //Reserved (28)
extern void __ISR_Exception_29(); //Reserved (29)
extern void __ISR_Exception_30(); //Reserved (30)
extern void __ISR_Exception_31(); //Reserved (31)
extern void __ISR_Exception_128(); //Reserved (128)

#endif
#endif