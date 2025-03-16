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
#include "menu.h"


// Struct that stores the commands received from instrument_cluster
struct report_info
{
    unsigned short right_signal;
    unsigned short left_signal;
    unsigned short high_headlights;
    unsigned short low_headlights;
    int throttle;
    int brakes;
};

volatile int paused = 0;

// Declaring variables globally so that its easier to terminate execution
int cluster_pid;
int simulator_pid;
mqd_t mq_receiver;
char *shm_ptr;
int shm_fd;
sem_t *sem;
struct report_info report = {0};



void pause_controller();

void terminate_all();

int execute_file(char *file_path);

void update_cluster_info(char *buffer);

void report_display();

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

    printf("[controller] Controller initialized with PID: %d\n", pid);

    sensors_info sinfo = {0};
    char mq_buffer[MQ_MAX_MSG_SIZE];

    while (1)
    {
        clear_screen();
        if(paused)
        {
            printf("Controller execution paused. Send SIGUSR1 to resume (kill -SIGUSR1 %d).\n", pid);
        }
        else
        {
            print_interface(pid);
            printf("[controller] Message received from mqueue: <%s>\n", mq_buffer);
            printf("[controller] Info received from shm: S: %*d, R: %*d, T: %*d\n", 3, sinfo.speed, 4, sinfo.rpm, 3, sinfo.temp);
            if(read_mq(mq_receiver, mq_buffer) == 0)
                update_cluster_info(mq_buffer);

            read_shm(shm_ptr, sem, &sinfo);
        }

        sleep(3);
    }

    terminate_all();

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

    close_mq(mq_receiver, MQ_NAME);
    
    report_display();


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

void update_cluster_info(char *buffer)
{
    switch (buffer[0])
    {
    case 'B':
        if(buffer[3] == '1')
            report.brakes++;
        break;
    case 'T':
        if(buffer[3] == '1')
            report.throttle++;
        break;
    case 'L':
        if(buffer[3] == '1')
            report.left_signal++;
        break;
    case 'R':
        if(buffer[3] == '1')
            report.right_signal++;
        break;
    case 'W':
        if(buffer[3] == '1')
            report.low_headlights++;
        break;
    case 'H':
        if(buffer[3] == '1')
            report.high_headlights++;
        break;
    
    default:
        break;
    }

}

void report_display()
{
    printf("\nReport - Activations sent by the user\n");
    printf("Accelerator: %d\n",report.throttle);
    printf("Brake: %d\n",report.brakes);
    printf("Right signal: %d\n",report.right_signal);
    printf("Left signal: %d\n",report.left_signal);
    printf("High headlights: %d\n",report.high_headlights);
    printf("Low headlights: %d\n",report.low_headlights);

}