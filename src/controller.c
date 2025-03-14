#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <mqueue.h>
#include <string.h>
#include <semaphore.h>
#include <signal.h>
#include "constants.h"
#include "mq_utils.h"
#include "shm_utils.h"

mqd_t mq_receiver;

void terminate_mq()
{
    printf("Closing message queue\n");
    close_mq(mq_receiver);
    exit(0);
}

int main()
{
    int pid = getpid();
    char mq_buffer[MQ_MAX_MSG_SIZE];

    printf("Controller initialized with PID: %d\n", pid);

    mq_receiver = create_mq(MQ_NAME);
    int shm_fd = create_shm(SHM_NAME);
    char *shm_ptr = map_shm(shm_fd, PROT_READ);
    sem_t *sem = create_sem(SEM_NAME);

    sensors_info sinfo = {0};

    while (1)
    {
        read_mq(mq_receiver, mq_buffer);
        read_shm(shm_ptr, sem, &sinfo);
        printf("Message received from mqueue: <%s>\n", mq_buffer);
        printf("Info received from shm: S: %*d, R: %*d, T: %*d ==\n", 3, sinfo.speed, 4, sinfo.rpm, 3, sinfo.temp);
        sleep(1);
    }

    close_mq(mq_receiver);
    munmap(shm_ptr, 4096);
    close(shm_fd);
    shm_unlink(SHM_NAME);
    sem_close(sem);
    sem_unlink(SEM_NAME);

    return 0;
}