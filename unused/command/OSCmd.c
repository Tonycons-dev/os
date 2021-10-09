#include "OSCmd.h"


const OSCommandInfo cCommandInfo[16] =
{
    [0] = {
        .command = OSCmd_Help,
        .name = "help",
        .desc = "Displays information about using the terminal.",
        .usage = "help :page:",
        .num_args = -1
    },
    {
        .command = OSCmd_Info,
        .name = "info",
        .desc = "Displays information about the usage and purpose of a command.",
        .usage = "info <command>",
        .num_args = 1,
    },
    {
        .command = OSCmd_CPUID,
        .name = "cpuid",
        .desc = "Displays information about the CPU model.",
        .usage = "cpuid",
        .num_args = 0
    },
    {
        .command = NULL,
        .name = "memsize",
        .desc = "Returns the amount of installed RAM.",
        .usage = "memsize",
        .num_args = 0
    },
    {
        .command = NULL,
        .name = "memfree",
        .desc = "Returns the amount of available RAM.",
        .usage = "memfree",
        .num_args = 0
    },
    {
        .command = NULL,
        .name = "disksize",
        .desc = "Displays storage capacity of the mounted disk.",
        .usage = "disksize :units: \n Units: B, MB, GB, TB",
        .num_args = -1
    },
    {
        .command = NULL,
        .name = "diskfree",
        .desc = "Displays the available space in the mounted disk.",
        .usage = "diskfree :units: \n Units: B, MB, GB, TB",
        .num_args = -1
    },
    {
        .command = NULL,
        .name = "disktype",
        .desc = "Displays the storage format of the mounted disk.",
        .usage = "disktype",
        .num_args = 0
    },
    {
        .command = NULL,
        .name = "pathsize",
        .desc = "Returns the maximum file path length.",
        .usage = "pathsize",
        .num_args = 0
    },
    {
        .command = NULL,
        .name = "cd",
        .desc = "Enter an existing subdirectory.",
        .usage = "cd <path>",
        .num_args = 1
    },
    {
        .command = NULL,
        .name = "ld",
        .desc = "Leave the current directory.",
        .usage = "ld",
        .num_args = 0
    },
    {
        .command = NULL,
        .name = "mkdir",
        .desc = "Create a new subdirectory in the current directory.",
        .usage = "mkdir <name>",
        .num_args = 1
    },
    {
        .command = NULL,
        .name = "rd",
        .desc = "Remove an existing subdirectory.",
        .usage = "rd <path>",
        .num_args = 1
    }
}