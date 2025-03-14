#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include "shm_utils.h"
#include "constants.h"

int cur_speed = 0;
int speed_increasing = 1;

int cur_rpm = 1000;
int rpm_increasing = 1;

void thread_sleep()
{
    usleep(100000 + rand() % 500000);
}

void *speed_thread(void *args)
{
    shm_args *arguments = (shm_args *)args;
    char *shm = arguments->shm;
    sem_t *sem = arguments->sem;

    while (1)
    {
        sem_wait(sem);
        if (speed_increasing)
        {
            cur_speed += rand() % 10;
            if (cur_speed >= 190)
                speed_increasing = 0;
        }
        else
        {
            cur_speed -= rand() % 10;
            if (cur_speed <= 10)
                speed_increasing = 1;
        }
        sprintf(shm, "S: %d", cur_speed);
        printf("<%s>\n", shm);
        sem_post(sem);
        thread_sleep();
    }
}

void *rpm_thread(void *args)
{
    shm_args *arguments = (shm_args *)args;
    char *shm = arguments->shm;
    sem_t *sem = arguments->sem;

    while (1)
    {
        sem_wait(sem);
        if (rpm_increasing)
        {
            cur_rpm += rand() % 100;
            if (cur_rpm >= 8000)
                rpm_increasing = 0;
        }
        else
        {
            cur_rpm -= rand() % 100;
            if (cur_rpm <= 1000)
                rpm_increasing = 1;
        }
        sprintf(shm, "R: %d", cur_rpm);
        printf("Message sent to shared memory: <%s>\n", shm);
        sem_post(sem);
        thread_sleep();
    }
}

int main()
{
    int shm_fd = open_shm(SHM_NAME);
    sem_t *sem = open_sem(SEM_NAME);
    char *shm_ptr = map_shm(shm_fd, PROT_WRITE);

    pthread_t thread1_id;
    pthread_t thread2_id;
    
    shm_args thread_args;
    thread_args.shm = shm_ptr;
    thread_args.sem = sem;

    pthread_create(&thread1_id, NULL, &speed_thread, &thread_args);
    pthread_create(&thread2_id, NULL, &rpm_thread, &thread_args);
    

    pthread_join(thread1_id, NULL);
    pthread_join(thread2_id, NULL);

    munmap(shm_ptr, 4096);
    close(shm_fd);
    sem_close(sem);

    return 0;
}