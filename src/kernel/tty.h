#ifndef _TERRA_KERNEL_TTY_
#define _TERRA_KERNEL_TTY_

#include "constants/types.h"

#define KTERMINAL_VGA_WIDTH         80
#define KTERMINAL_VGA_HEIGHT        24

typedef enum {
    COLOR_BLACK,
    COLOR_BLUE,
    COLOR_GREEN,
    COLOR_CYAN,
    COLOR_RED,
    COLOR_MAGENTA,
    COLOR_BROWN,
    COLOR_GREY,
    COLOR_DARK_GREY,
    COLOR_BRIGHT_BLUE,
    COLOR_BRIGHT_GREEN,
    COLOR_BRIGHT_CYAN,
    COLOR_BRIGHT_RED,
    COLOR_BRIGHT_MAGENTA,
    COLOR_YELLOW,
    COLOR_WHITE,
} VgaColorType;

void KTerminalInit(uint8 foreground, uint8 background);
void KTerminalClear(uint8 foreground, uint8 background);
void KTerminalPutChar(char character);
void KTerminalPutString(const char* message);
void KTerminalWrite(const char* format, ...);
void KTerminalNewLine();
void KTerminalRemoveChar();
void KTerminalRemoveChars(uint8 count);
void KTerminalSetXY(uint16 x, uint16 y);
void KTerminalSetCursor(uint16 x, uint16 y);
void KTerminalDisableCursor(void);

#endif