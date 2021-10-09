#include "kernel/tty.h"
#include "ports.h"

#define KTERMINAL_VGA_ADDRESS       0xB8000
#define KTERMINAL_VGA_TOTAL_ITEMS   2200

static uint16* gVGABuffer;
static uint32 gVGAIndex;
static uint8 gCursorPosX = 0, gCursorPosY = 0;
static uint8 gForeColor = 0, gBackColor = 0;


uint16 KTerminalItemEntry(uint8 ch, uint16 fore, uint16 back)
{
    uint16 ax = 0;
    uint8 ah = 0, al = 0;

    ah = back;
    ah <<= 4;
    ah |= fore;
    ax = ah;
    ax <<= 8;
    al = ch;
    ax |= al;

    return ax;
}

void KTerminalClear(uint8 foreground, uint8 background)
{
    for (uint32 i = 0; i < KTERMINAL_VGA_TOTAL_ITEMS; i++)
        gVGABuffer[i] = KTerminalItemEntry(0, foreground, background);

    gVGAIndex = 0;
    gCursorPosX = 0;
    gCursorPosY = 0;

    KTerminalSetCursor(gCursorPosX, gCursorPosY);
}

void KTerminalInit(uint8 foreground, uint8 background)
{
    gVGABuffer = (uint16*)KTERMINAL_VGA_ADDRESS;
    gForeColor = foreground;
    gBackColor = background;
    gCursorPosX = 0;
    gCursorPosY = 0;

    KTerminalClear(foreground, background);
}

void KTerminalNewLine()
{
    if (gCursorPosY >= KTERMINAL_VGA_HEIGHT) 
    {
        gCursorPosX = 0;
        gCursorPosY = 0;

        KTerminalClear(gForeColor, gBackColor);
    } 
    else 
    {
        gVGAIndex += KTERMINAL_VGA_WIDTH - (gVGAIndex % KTERMINAL_VGA_WIDTH);
        gCursorPosX = 0;
        ++gCursorPosY;

        KTerminalSetCursor(gCursorPosX, gCursorPosY);
    }
}

void KTerminalPutChar(char character)
{
    if (character == ' ')
    {
        gVGABuffer[gVGAIndex++] = KTerminalItemEntry(' ', gForeColor, gBackColor);
        KTerminalSetCursor(gCursorPosX++, gCursorPosY);
    }
    else if (character == '\t')
    {
        for (int i = 0; i < 4; i++)
        {
            gVGABuffer[gVGAIndex++] = KTerminalItemEntry(' ', gForeColor, gBackColor);
            KTerminalSetCursor(gCursorPosX++, gCursorPosY);            
        }
    }
    else if (character == '\n')
    {
        KTerminalNewLine();
    }
    else if (character > 0)
    {
        gVGABuffer[gVGAIndex++] = KTerminalItemEntry(character, gForeColor, gBackColor);
        KTerminalSetCursor(gCursorPosX++, gCursorPosY);
    }
}

void KTerminalPutString(const char* message)
{
    uint32 index = 0U;

    while (message[index] != '\0')
    {
        if (message[index] == '\n')
            KTerminalNewLine();
        else
            KTerminalPutChar(message[index]);

        ++index;
    }
}

void KTerminalRemoveChar()
{
    if (gVGAIndex == 0)
        goto __done;

    gVGABuffer[gVGAIndex--] = KTerminalItemEntry(0, gForeColor, gBackColor);

    if (gCursorPosX == 0)
    {
        gCursorPosX = KTERMINAL_VGA_WIDTH;

        if (gCursorPosY > 0)
            KTerminalSetCursor(gCursorPosX--, --gCursorPosY);
        else
            gCursorPosY = 0;

        goto __done;
    }

    KTerminalSetCursor(gCursorPosX--, gCursorPosY);  
    __done:

    gVGABuffer[gVGAIndex] = KTerminalItemEntry(0, gForeColor, gBackColor);
}

void KTerminalRemoveChars(uint8 count)
{
    if(!(((gVGAIndex % KTERMINAL_VGA_WIDTH) > count) && (count > 0)))
        goto __done;

    gVGABuffer[gVGAIndex--] = KTerminalItemEntry(0, gForeColor, gBackColor);

    if (gCursorPosX < count)
    {
        gCursorPosX = KTERMINAL_VGA_WIDTH;

        if (gCursorPosY > 0)
            KTerminalSetCursor(gCursorPosX--, --gCursorPosY);
        else
            gCursorPosY = 0;
        goto __done;
    }

    KTerminalSetCursor(gCursorPosX--, gCursorPosY);  
    __done:

    gVGABuffer[gVGAIndex] = KTerminalItemEntry(0, gForeColor, gBackColor);
}

void KTerminalSetXY(uint16 x, uint16 y)
{
    gVGAIndex = (KTERMINAL_VGA_WIDTH * y) + x;
    gCursorPosX = x;
    gCursorPosY = y;

    KTerminalSetCursor(gCursorPosX, gCursorPosY);
}

void KTerminalSetCursor(uint16 x, uint16 y)
{
    uint16 cursorLocation = y * KTERMINAL_VGA_WIDTH + x;

    __writeb(0x3D4, 14);
    __writeb(0x3D5, cursorLocation >> 8);
    __writeb(0x3D4, 15);
    __writeb(0x3D5, cursorLocation);
}

void KTerminalDisableCursor(void)
{
    __writeb(0x3D4, 10);
    __writeb(0x3D5, 32);
}

/*
void KTerminalWrite(const char* format, ...)
{
    char** arg = (char**)&format;
    int character;
    char buffer[32];

    arg++;
    ZeroMemory(buffer, sizeof(buffer));

    while ((character = *format++) != 0)
    {
        if (character != '%') {
            KTerminalPutChar(character);
            continue;         
        }

        char* p, *p2;
        int pad0 = 0, pad = 0;
        
        character = *format++;

        if (character == '0') {
            pad0 = 1;
            character = *format++;
        }
        if (character >= '0' && character <= '9') {
            pad = character - '0';
            character = *format++;
        }
            
        switch (character)
        {
        case 'd':
        case 'u':
        case 'i':
            IntToString(buffer, 10, *((int*)arg++));
            p = buffer;
            break;
            
        case 'x':
            IntToString(buffer, 16, *((int*)arg++));
            p = buffer;
            break;

        case 's':
            p = *arg++;
            if (!p)
                p = "(null)";
            break;

        string:
            for (p2 = p; *p2; p2++)
                ;
            for (; p2 < p + pad; p2++)
                KTerminalPutChar(pad0 ? '0' : ' ');
            while (*p)
                KTerminalPutChar(*p++);
            break;
            
        default:
            KTerminalPutChar(*((int*)arg++));
            break;
        }
    }
}
*/