#ifdef __X86_64__
#ifndef _OS_platform_X86_REGISTERS_
#define _OS_platform_X86_REGISTERS_

#include "constants/types.h"

typedef struct
{
    uint32 ds;
    uint32 edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32 int_no, err_code;
    uint32 eip, cs, eflags, useresp, ss;
} _Registers;
typedef _Registers X86Registers;

void __PrintRegisters(_Registers* registers);

#endif
#endif