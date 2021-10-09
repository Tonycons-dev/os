#ifndef _OS_KERNEL_COMMAND_
#define _OS_KERNEL_COMMAND_

#include "../OSTypes.h"
#include "../../../libc/include/string.h"

#define OS_COMMAND_ERROR 0
#define OS_COMMAND_OK 1
#define OS_COMMAND_FAIL -1

typedef struct
{
    const char* name;
    const char** args;
    int num_args;
} OSCommand;

typedef struct
{
    int ok;
    const char* message;
} OSCommandResult;

typedef void (*OSCommandFunc)(OSCommand*);

typedef struct
{
    const OSCommandFunc command;    
    const char* name;
    const char* desc;
    const char* usage;
    const int num_args;
} OSCommandInfo;


extern const OSCommandInfo gCommandInfo[16];

OSCommandResult OSCmd_CPUID(OSCommand* command);
OSCommandResult OSCmd_Help(OSCommand* command);
OSCommandResult OSCmd_Info(OSCommand* command);

#endif