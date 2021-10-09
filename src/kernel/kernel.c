#include "tty.h"


void kmain(void)
{
    KTerminalInit(COLOR_WHITE, COLOR_BLACK);
    KTerminalPutString("Hello World!");

    while (1){}
}