#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct
{
    int rpm;
    int speed;
    int temp;
} sensors_info;

typedef struct
{
    int left_turn_signal;
    int right_turn_signal;
    int low_headl;
    int high_headl;
    int throttle;
    int breaks;
} cluster_info;

#endif