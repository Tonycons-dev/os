#ifdef __X86_64__
#ifndef _OS_platform_X86_VGA_CONTROLLER_
#define _OS_platform_X86_VGA_CONTROLLER_

#define VGA_ADDRESS         0xB8000
#define VGA_TOTAL_ITEMS     2200
#define VGA_WIDTH           80
#define VGA_HEIGHT          24

typedef enum 
{
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

typedef enum
{
    VGA_MODE_TERMINAL,
    VGA_MODE_GRAPHICS
} VgaMode;

/**
 * 16 bit video buffer elements(register ax)
 * 8 bits(ah) higher : 
 * lower 4 bits - forec olor
 * higher 4 bits - back color
 * 8 bits(al) lower :
 * 8 bits : ASCII character to print
 * 
 * returns complete item with fore & back color to be placed at VGA address
*/
unsigned short VgaItemEntry(unsigned char ch, int fColor, int bColor);

void VgaEnableConsoleMode();
void VgaDisableConsoleMode();
void VgaSetCursorPos(unsigned char x, unsigned char y);
void VgaDisableCursor();

#endif
#endif