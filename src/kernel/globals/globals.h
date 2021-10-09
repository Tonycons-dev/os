#ifndef _TERRA_KERNEL_GLOBALS_
#define _TERRA_KERNEL_GLOBALS_

#ifdef __cplusplus
extern "C" {
#endif

#include "constants/types.h"

extern char gKeyChar;
extern uint8 gCapsLock;
extern uint8 gKeyShift;

extern uint8 gKeysPressed[128];
extern uint8 gKeysReleased[128];
extern char gScancodeChars[128];

#ifdef __cplusplus
}
#endif
#endif