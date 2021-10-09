#ifdef __X86_64__
#include "x86_vga_controller.h"
#include "platform/x86/io/x86Ports.h"

VgaMode gVgaMode;

unsigned short VgaItemEntry(unsigned char ch, int fColor, int bColor)
{
    unsigned short ax = 0;
    unsigned char ah = 0, al = 0;

    ah = bColor;
    ah <<= 4;
    ah |= fColor;
    ax = ah;
    ax <<= 8;
    al = ch;
    ax |= al;

    return ax;
}

void VgaDisableCursor()
{
    if (gVgaMode != VGA_MODE_TERMINAL)
        return;

    __writeb(0x3D4, 10);
    __writeb(0x3D5, 32);
}

void VgaSetCursorPos(unsigned char x, unsigned char y)
{
    if (gVgaMode != VGA_MODE_TERMINAL)
        return;

    unsigned short cursorLocation = y * VGA_WIDTH + x;

    __writeb(0x3D4, 14);
    __writeb(0x3D5, cursorLocation >> 8);
    __writeb(0x3D4, 15);
    __writeb(0x3D5, cursorLocation);
}

#endif