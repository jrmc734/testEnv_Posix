#ifndef MQ_UTILS_H
#define MQ_UTILS_H
#include <mqueue.h>

typedef struct
{
    int left_turn_signal;
    int right_turn_signal;
    int low_headl;
    int high_headl;
    int throttle;
    int breaks;
} cluster_info;

struct mq_attr get_mq_attr();

mqd_t create_mq(char *mq_name);

mqd_t open_mq(char *mq_name);

void close_mq(mqd_t mqd, char *mq_name);

int read_mq(mqd_t mq_receiver, char* buffer);

int write_mq(mqd_t mq_sender, char *msg);

#endif