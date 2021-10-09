#ifdef __X86_64__
#ifndef _OS_platform_X86_KEYBOARD_ACCESS_
#define _OS_platform_X86_KEYBOARD_ACCESS_

#include "platform/x86/registers/x86_registers.h"


void KeyboardInit(void);

uint8 OSKeyboardKeyPressed(uint8 scancode);
uint8 OSKeyboardKeyReleased(uint8 scancode);
uint8 OSGetChar();

void KeyboardInterruptHandler(X86Registers* registers);

#endif
#endif