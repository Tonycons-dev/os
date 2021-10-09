#ifndef _OS_KERNEL_
#define _OS_KERNEL_

#include "OSTypes.h"
#include "../include/stddef.h"

int _Printf(const char* format, ...);
int printf(const char* format, ...);

#endif