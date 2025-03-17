#include "constants.h"
#include <stdio.h>

void clear_screen()
{
    printf("\e[1;1H\e[2J"); // clear screen
}

void print_header(int pid)
{
    printf("========================================\n");
    printf("======  Controller PID: %*d  ======\n", 8, pid);
    printf("========================================\n");
    printf("========       Dashboard        ========\n");
}

void print_user_menu()
{
    printf("========================================\n");
    printf("==  Type one of the commands below    ==\n");
    printf("==         and press ENTER            ==\n");
    printf("=== %c: Activate/deactivate throttle  ===\n", THR_COMMAND);
    printf("=== %c: Activate/deactivate breaks    ===\n", BRK_COMMAND);
    printf("=== %c: Turn on/off low headlights    ===\n", LHL_COMMAND);
    printf("=== %c: Turn on/off high headlights   ===\n", HHL_COMMAND);
    printf("=== %c: Turn on/off left turn signal  ===\n", LTS_COMMAND);
    printf("=== %c: Turn on/off right turn signal ===\n", RTS_COMMAND);
    printf("========================================\n");
}
