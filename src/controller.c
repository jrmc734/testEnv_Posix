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

volatile int paused = 0;

// Declaring variables globally so that its easier to terminate execution
int cluster_pid;
int simulator_pid;
mqd_t mq_receiver;
char *shm_ptr;
int shm_fd;
sem_t *sem;

void pause_controller();

void terminate_all();

int execute_file(char *file_path);

int main()
{
    int pid = getpid();

    signal(SIGINT, terminate_all);
    signal(SIGUSR1, pause_controller);
    signal(SIGUSR2, terminate_all);

    mq_receiver = create_mq(MQ_NAME);
    shm_fd = create_shm(SHM_NAME);
    shm_ptr = map_shm(shm_fd, PROT_READ);
    sem = create_sem(SEM_NAME);

    cluster_pid = execute_file("bin/instrument_cluster_bin");
    simulator_pid = execute_file("bin/sensor_simulator_bin");

    sleep(1);

    char mq_buffer[MQ_MAX_MSG_SIZE];

    printf("[controller] Controller initialized with PID: %d\n", pid);

    sensors_info sinfo = {0};

    while (1)
    {
        read_mq(mq_receiver, mq_buffer);
        read_shm(shm_ptr, sem, &sinfo);
        printf("[controller] Message received from mqueue: <%s>\n", mq_buffer);
        printf("[controller] Info received from shm: S: %*d, R: %*d, T: %*d\n", 3, sinfo.speed, 4, sinfo.rpm, 3, sinfo.temp);
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

void pause_controller()
{
    paused = !paused;
}

void terminate_all()
{
    printf("\nTerminating all processes...\n");

    kill(cluster_pid, SIGINT);
    kill(simulator_pid, SIGINT);

    munmap(shm_ptr, 4096);
    close(shm_fd);
    shm_unlink(SHM_NAME);

    sem_close(sem);
    sem_unlink(SEM_NAME);

    close_mq(mq_receiver);

    exit(0);
}

int execute_file(char *file_path)
{
    int pid = fork();
    if (pid == 0)
    {
        execl(file_path, file_path, NULL);
        perror("execl failed");  // Mostra erro caso a execução falhe
        exit(EXIT_FAILURE);      // Finaliza o processo filho se houver falha
    }
    return pid;
}