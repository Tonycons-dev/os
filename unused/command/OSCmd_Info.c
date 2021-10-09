#include "OSCmd.h"


OSCommandResult OSCmd_Info(OSCommand* command)
{
    if (command->num_args < 1)
    return (OSCommandResult)
    { 
        .ok = OS_COMMAND_ERROR, 
        .message = "Specify a command name as the argument."
    };

    if (command->num_args > 1)
    return (OSCommandResult)
    {
        .ok = OS_COMMAND_ERROR,
        .message = "Specify only one command name as the argument."
    };

    const char* commandName = command->args[0];

    for (int i = 0; i < sizeof(gCommandInfo); i++)
    {
        if (strcmp(commandName, gCommandInfo[i].name) == 0)
        {
            printf("%s\n", gCommandInfo[i].desc);
            return (OSCommandResult)
            {
                .ok = OS_COMMAND_OK,
                .message = gCommandInfo[i].usage
            };            
        }
    }
    return (OSCommandResult)
    {
        .ok = OS_COMMAND_FAIL,
        .message = "The specified command name is not recognized as a command."
    };
}