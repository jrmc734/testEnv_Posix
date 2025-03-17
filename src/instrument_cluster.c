#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <mqueue.h>
#include <string.h>
#include <semaphore.h>
#include "constants.h"
#include "mq_utils.h"
#include "menu.h"

int main()
{
    mqd_t mq_sender = open_mq(MQ_NAME);
    char buffer[MQ_MAX_MSG_SIZE];

    char command;

    int lts_on = 0;  // left turn signal
    int rts_on = 0;  // right turn signal
    int lhl_on = 0;  // low headlights
    int hhl_on = 0;  // high headlights
    int thrt_on = 0; // throttle
    int brks_on = 0; // breaks

    while (1)
    {
        scanf(" %c", &command);
        if (command == LTS_COMMAND)
        {
            if (rts_on)
                printf("Can't turn on both turn signals at the same time\n");
            else
            {
                lts_on = !lts_on;
                sprintf(buffer, "%c: %d", command, lts_on);
            }
        }
        else if (command == RTS_COMMAND)
        {
            if (lts_on)
                printf("Can't turn on both turn signals at the same time\n");
            else
            {
                rts_on = !rts_on;
                sprintf(buffer, "%c: %d", command, rts_on);
            }
        }
        else if (command == LHL_COMMAND)
        {
            lhl_on = !lhl_on;
            sprintf(buffer, "%c: %d", command, lhl_on);
        }
        else if (command == HHL_COMMAND)
        {
            hhl_on = !hhl_on;
            sprintf(buffer, "%c: %d", command, hhl_on);
        }
        else if (command == THR_COMMAND)
        {
            if (brks_on)
                printf("Can't turn throttle on with breaks on\n");
            else
            {
                thrt_on = !thrt_on;
                sprintf(buffer, "%c: %d", command, thrt_on);
            }
        }
        else if (command == BRK_COMMAND)
        {
            if (thrt_on)
                printf("Can't turn breaks on with throttle on\n");
            else
            {
                brks_on = !brks_on;
                sprintf(buffer, "%c: %d", command, brks_on);
            }
        }
        else
        {
            sprintf(buffer, "NULL");
        }

        write_mq(mq_sender, buffer);
      //  printf("[instrument_cluster]: <%s>\n", buffer);
        sleep(1);
    }

    return 0;
}