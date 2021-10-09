#ifdef __X86_64__

#include "x86KeyboardHandler.h"
#include "platform/x86/input/x86Ports.h"
#include "platform/x86/int/x86_isr.h"
#include "platform/x86/int/x86_irq.h"
#include "constants/key_codes.h"
#include "globals/key_values.h"
#include "utils/keyboard.h"

#define __X86_KEYBOARD_DATA_PORT         0x60
#define __X86_KEYBOARD_STATUS_PORT       0x64
#define __X86_KEYBOARD_COMMAND_PORT      0x64

int __GetKeyScancode(void)
{
    int i, scancode = 0;

    for (i = 1000; i > 0; i++)
    {
        unsigned char value;
        value = __readb(__X86_KEYBOARD_STATUS_PORT);

        if ((value & 1) == 0)
            continue;

        value = __readb(__X86_KEYBOARD_DATA_PORT);  
        scancode = (int)value;
        break;
    }

    if (i > 0)
        return scancode;

    return 0;  
}

void KeyboardInterruptHandler(X86Registers* registers)
{
    int scancode;
    gChar = 0;

    scancode = __GetKeyScancode();

    gKeysReleased[scancode] = 0;
    gKeysPressed[scancode] = 0;
    
    if (scancode & 0x80) 
    {
        gKeysReleased[scancode] = 1;
    }
    else switch (scancode)
    {
        gKeysPressed[scancode] = 1;
        
    case KEY_SCAN_CODE_CAPS_LOCK:
        gCapsLock = !gCapsLock;
        break;

    case KEY_SCAN_CODE_ENTER:
        gCapsLock = '\n';
        break;

    case KEY_SCAN_CODE_TAB:
        gChar = '\t';
        break;

    case KEY_SCAN_CODE_LEFT_SHIFT:
        gKeyShift = 1;
        break;

    default:
        gChar = gScancodeChars[scancode];

        if (gCapsLock)
        {
            if (gKeyShift)
                gChar = ShiftChars(gChar);
            else
                gChar = upper(gChar);
        }
        else
        {
            if (gKeyShift)
            {
                if (isalpha(gChar))
                    gChar = upper(gChar);
                else
                    gChar = ShiftChars(gChar);
            }
            gKeyShift = 0;
        }
        break;
    }
}

void KeyboardInit(void)
{
    ISRRegisterInterruptHandler(IRQ_BASE + 1, KeyboardInterruptHandler);
}

#endif