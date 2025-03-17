#include <sys/stat.h>
#define UNITY_VERBOSE_OUTPUT
#include "unity.h"
#include "shm_utils.h"
#include "constants.h"
#include <semaphore.h>
#include <fcntl.h>
#include <sys/mman.h>

void setUp(void)
{
    // set stuff up here
}

void tearDown(void)
{
    // clean stuff up here
}

void test_create_shm(void)
{
    char *shm_name = "/my_shm";
    struct stat buffer;

    int exists = stat("/dev/shm/my_shm", &buffer);
    TEST_ASSERT_EQUAL(-1, exists);

    int shm_fd = create_shm(shm_name);

    exists = stat("/dev/shm/my_shm", &buffer);
    TEST_ASSERT_EQUAL(0, exists);

    close(shm_fd);
    shm_unlink(shm_name);
    exists = stat("/dev/shm/my_shm", &buffer);
    TEST_ASSERT_EQUAL(-1, exists);
}

void test_open_shm(void)
{
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    TEST_ASSERT_NOT_EQUAL(-1, shm_fd);
    close(shm_fd);

    shm_fd = open_shm(SHM_NAME);
    TEST_ASSERT_NOT_EQUAL(-1, shm_fd);
    close(shm_fd);
    shm_unlink(SHM_NAME);
}

void test_map_shm(void)
{
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, 4096);
    TEST_ASSERT_NOT_EQUAL(-1, shm_fd);

    char *shm_ptr = map_shm(shm_fd, PROT_READ | PROT_WRITE);
    TEST_ASSERT_NOT_EQUAL(MAP_FAILED, shm_ptr);

    munmap(shm_ptr, 4096);
    close(shm_fd);
    shm_unlink(SHM_NAME);
}

void test_create_sem(void)
{
    sem_t *sem = create_sem(SEM_NAME);
    TEST_ASSERT_NOT_NULL(sem);
    sem_close(sem);
    sem_unlink(SEM_NAME);
}

void test_open_sem(void)
{
    sem_t *sem = sem_open(SEM_NAME, O_CREAT, 0666, 1);
    sem_close(sem);

    sem = open_sem(SEM_NAME);
    TEST_ASSERT_NOT_NULL(sem);
    sem_close(sem);
    sem_unlink(SEM_NAME);
}

void test_read_shm(void)
{
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, 4096);
    char *shm_ptr = map_shm(shm_fd, PROT_READ | PROT_WRITE);
    sem_t *sem = create_sem(SEM_NAME);
    sensors_info sinfo;

    strcpy(shm_ptr, "R: 3000");
    read_shm(shm_ptr, sem, &sinfo);
    TEST_ASSERT_EQUAL(3000, sinfo.rpm);

    strcpy(shm_ptr, "S: 80");
    read_shm(shm_ptr, sem, &sinfo);
    TEST_ASSERT_EQUAL(80, sinfo.speed);

    strcpy(shm_ptr, "T: 100");
    read_shm(shm_ptr, sem, &sinfo);
    TEST_ASSERT_EQUAL(100, sinfo.temp);

    munmap(shm_ptr, 4096);
    close(shm_fd);
    shm_unlink(SHM_NAME);
    sem_close(sem);
    sem_unlink(SEM_NAME);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_open_shm);
    RUN_TEST(test_map_shm);
    RUN_TEST(test_create_sem);
    RUN_TEST(test_open_sem);
    RUN_TEST(test_read_shm);
    return UNITY_END();
}