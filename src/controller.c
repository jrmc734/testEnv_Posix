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
    // int shm_fd = create_shm(SHM_NAME);
    // char *shm_ptr = map_shm(shm_fd, PROT_READ);
    // sem_t *sem = create_sem(SEM_NAME);

    while (1)
    {
        read_mq(mq_receiver, mq_buffer);
        printf("Received message: <%s>\n", mq_buffer);
        sleep(1);
    }

    close_mq(mq_receiver);
    // munmap(shm_ptr, 4096);
    // close(shm_fd);
    // shm_unlink(SHM_NAME);
    // sem_close(sem);
    // sem_unlink(SEM_NAME);

    return 0;
}