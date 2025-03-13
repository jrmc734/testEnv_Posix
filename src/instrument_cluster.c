#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
#include <unistd.h>
#include "constants.h"
#include "mq_utils.h"

int main()
{
    mqd_t mq_sender = open_mq(MQ_NAME);
    char buffer[MQ_MAX_MSG_SIZE];

    while (1)
    {
        sprintf(buffer, "Message from IC: %d", rand() % 100);
        write_mq(mq_sender, buffer);
        printf("Message sent: <%s>\n", buffer);
        sleep(1);
    }

    return 0;
}