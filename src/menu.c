#include "constants.h"
#include "structs.h"
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

void print_cluster_info(cluster_info cinfo)
{
    printf("====   LTS: %*s          RTS: %*s   ====\n", 3, cinfo.left_turn_signal ? "ON" : "OFF", 3, cinfo.right_turn_signal ? "ON" : "OFF");
    printf("====   LHL: %*s          HHL: %*s   ====\n", 3, cinfo.low_headl ? "ON" : "OFF", 3, cinfo.high_headl ? "ON" : "OFF");
    printf("====   THR: %*s          BRK: %*s   ====\n", 3, cinfo.throttle ? "ON" : "OFF", 3, cinfo.breaks ? "ON" : "OFF");
}

void print_sensors_info(sensors_info sinfo)
{
    printf("== Speed: %*d   Rpm: %*d   Temp: %*d ==\n", 3, sinfo.speed, 4, sinfo.rpm, 3, sinfo.temp);
}

void print_interface(int pid, sensors_info sinfo, cluster_info cinfo)
{
    printf("\n");
    print_header(pid);
    print_cluster_info(cinfo);
    print_sensors_info(sinfo);
    print_user_menu();
    printf("\n");
}