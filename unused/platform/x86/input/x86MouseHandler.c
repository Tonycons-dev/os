#ifdef __X86_64__

#include "x86MouseHandler.h"
#include "platform/x86/input/x86Ports.h"
#include "platform/x86/int/x86_isr.h"
#include "platform/x86/int/x86_irq.h"
#include "utils/kdebug.h"

int gMouseXPos = 0;
int gMouseYPos = 0;
int gMouseXLimit = 0;
int gMouseYLimit = 0;



void MouseWait(uint8 type)
{
    uint32 timeout = 100000;

    if (type == 0)
    {
        while (timeout--)
        if ((__readb(PS2_CMD_PORT) & 1) == 1)
            return;
    }
    else
    {
        while (timeout--)
        if ((__readb(PS2_CMD_PORT) & 2) == 0)
            return;
    }
}

void MouseWrite(uint8 data)
{
    MouseWait(1);
    __writeb(PS2_CMD_PORT, 0xD4);

    MouseWait(1);
    __writeb(MOUSE_DATA_PORT, data);
}

uint8 MouseRead(void)
{
    MouseWait(0);
    return __readb(MOUSE_DATA_PORT);
}

void MouseGetStatus(char status, MouseStatus* mouse)
{
    *mouse = (MouseStatus)
    {
    .left_button   = status & 0x01 ? 1 : 0,
    .right_button  = status & 0x02 ? 1 : 0,
    .middle_button = status & 0x04 ? 1 : 0,
    .always_1      = status & 0x08 ? 1 : 0,
    .x_sign        = status & 0x10 ? 1 : 0,
    .y_sign        = status & 0x20 ? 1 : 0,
    .x_overflow    = status & 0x40 ? 1 : 0,
    .y_overflow    = status & 0x80 ? 1 : 0,
    };
}

void MouseInterrupt(X86Registers* registers)
{
    static uint8 mouse_cycle = 0;
    static char mouse_byte[3];
    MouseStatus status;

    switch (mouse_cycle) 
    {
    case 0:
        mouse_byte[0] = MouseRead();
        MouseGetStatus(mouse_byte[0], &status);

        mouse_cycle++;
        break;

    case 1:
        mouse_byte[1] = MouseRead();
        mouse_cycle++;
        break;

    case 2:
        mouse_byte[2] = MouseRead();

        if (mouse_byte[1] == 0 && mouse_byte[2] == 0)
            break;

        if(status.x_sign)
            gMouseXPos += mouse_byte[1];
        else
            gMouseXPos += mouse_byte[1];
    
        gMouseYPos -= mouse_byte[2];

        if (gMouseXPos < 0)
            gMouseXPos = 0;

        if (gMouseYPos < 0)
            gMouseYPos = 0;

        if (gMouseXPos > (gMouseXLimit * gMouseYLimit))
            gMouseXPos = (gMouseXLimit * gMouseYLimit) - 1;

        if (gMouseYPos > gMouseYLimit)
            gMouseYPos = gMouseYLimit - 1;

        mouse_cycle = 0;
        break;
    }

    ISREndInterrupt(IRQ_BASE + 12);
}

void MouseSetRate(uint8 rate)
{
    uint8 status;

    __writeb(MOUSE_DATA_PORT, MOUSE_CMD_SAMPLE_RATE);
    status = MouseRead();

    if (status != MOUSE_ACKNOWLEDGE)
    {
        kerror("Failed to send mouse sample rate command");
        return;
    }

    __writeb(MOUSE_DATA_PORT, rate);
    status = MouseRead();

    if (status != MOUSE_ACKNOWLEDGE)
    {
        kerror("Failed to send mouse sample rate data");
        return;
    }
}

void MouseInit(void)
{
    uint8 status;

    gMouseXPos = 5;
    gMouseYPos = 2;

    kprintf("Initializing mouse...");

    MouseWait(1);
    __writeb(PS2_CMD_PORT, 0xA8);

    __writeb(MOUSE_DATA_PORT, MOUSE_CMD_MOUSE_ID);
    status = MouseRead();

    kprintf("Mouse ID: 0x%x\n", status);

    MouseSetRate(10);

    MouseWait(1);
    __writeb(PS2_CMD_PORT, 0x20);
    MouseWait(0);

    status = (__readb(MOUSE_DATA_PORT) | 2);

    MouseWait(1);
    __writeb(PS2_CMD_PORT, MOUSE_DATA_PORT);

    MouseWait(1);
    __writeb(MOUSE_DATA_PORT, status);

    MouseWrite(MOUSE_CMD_SET_DEFAULTS);
    status = MouseRead();

    if (status != MOUSE_ACKNOWLEDGE)
    {
        kerror("Failed to set default mouse settings");
        return;
    }

    MouseWrite(MOUSE_CMD_ENABLE_PACKET_STREAMING);
    status = MouseRead();

    if (status != MOUSE_ACKNOWLEDGE)
    {
        kerror("Failed to enable mouse packet streaming");
        return;
    }

    ISRRegisterInterruptHandler(IRQ_BASE + 12, MouseInterrupt);
}

#endif