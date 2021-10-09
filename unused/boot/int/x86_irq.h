#ifdef __X86_64__
#ifndef _OS_platform_X86_IRQ_
#define _OS_platform_X86_IRQ_

#include "platform/x86/registers/x86_registers.h"

#define IRQ_BASE            0x20
#define IRQ0_TIMER          0x00
#define IRQ1_KEYBOARD       0x01
#define IRQ2_CASCADE        0x02
#define IRQ3_SERIAL_PORT2   0x03
#define IRQ4_SERIAL_PORT1   0x04
#define IRQ5_RESERVED       0x05
#define IRQ6_DISKETTE_DRIVE 0x06
#define IRQ7_PARALLEL_PORT  0x07
#define IRQ8_CMOS_CLOCK     0x08
#define IRQ9_CGA            0x09
#define IRQ10_RESERVED      0x0A
#define IRQ11_RESERVED      0x0B
#define IRQ12_AUXILIARY     0x0C
#define IRQ13_FPU           0x0D
#define IRQ14_HARD_DISK     0x0E
#define IRQ15_RESERVED      0x0F

void IRQHandler(X86Registers* registers);

extern void __IRQ_Interrupt_00();
extern void __IRQ_Interrupt_01();
extern void __IRQ_Interrupt_02();
extern void __IRQ_Interrupt_03();
extern void __IRQ_Interrupt_04();
extern void __IRQ_Interrupt_05();
extern void __IRQ_Interrupt_06();
extern void __IRQ_Interrupt_07();
extern void __IRQ_Interrupt_08();
extern void __IRQ_Interrupt_09();
extern void __IRQ_Interrupt_10();
extern void __IRQ_Interrupt_11();
extern void __IRQ_Interrupt_12();
extern void __IRQ_Interrupt_13();
extern void __IRQ_Interrupt_14();
extern void __IRQ_Interrupt_15();

#endif
#endif