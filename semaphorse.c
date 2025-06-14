#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>           // For O_* constants
#include <sys/mman.h>        // For shm
#include <sys/wait.h>        // For wait

#define SHM_NAME "/rw_shm"
#define SEM_MUTEX "/mutex_sem"
#define SEM_WRITE "/write_sem"

typedef struct {
    int readCount;
    int data; // shared data (e.g., a variable)
} SharedMemory;

int main() {
    int i;
    pid_t reader1, reader2, writer;

    // Create shared memory
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, sizeof(SharedMemory));
    SharedMemory *shm = (SharedMemory *)mmap(0, sizeof(SharedMemory), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    shm->readCount = 0;
    shm->data = 0;

    // Create semaphores
    sem_t *mutex = sem_open(SEM_MUTEX, O_CREAT, 0666, 1);
    sem_t *wrt = sem_open(SEM_WRITE, O_CREAT, 0666, 1);

    // Fork writer process
    writer = fork();
    if (writer == 0) {
        for (i = 0; i < 5; i++) {
            sem_wait(wrt);
            shm->data += 10;
            printf("Writer wrote: %d\n", shm->data);
            sem_post(wrt);
            sleep(2);
        }
        exit(0);
    }

    // Fork first reader
    reader1 = fork();
    if (reader1 == 0) {
        for (i = 0; i < 5; i++) {
            sem_wait(mutex);
            shm->readCount++;
            if (shm->readCount == 1)
                sem_wait(wrt);
            sem_post(mutex);

            printf("Reader 1 read: %d\n", shm->data);

            sem_wait(mutex);
            shm->readCount--;
            if (shm->readCount == 0)
                sem_post(wrt);
            sem_post(mutex);
            sleep(1);
        }
        exit(0);
    }

    // Fork second reader
    reader2 = fork();
    if (reader2 == 0) {
        for (i = 0; i < 5; i++) {
            sem_wait(mutex);
            shm->readCount++;
            if (shm->readCount == 1)
                sem_wait(wrt);
            sem_post(mutex);

            printf("Reader 2 read: %d\n", shm->data);

            sem_wait(mutex);
            shm->readCount--;
            if (shm->readCount == 0)
                sem_post(wrt);
            sem_post(mutex);
            sleep(1);
        }
        exit(0);
    }

    // Wait for children
    wait(NULL);
    wait(NULL);
    wait(NULL);

    // Cleanup
    sem_unlink(SEM_MUTEX);
    sem_unlink(SEM_WRITE);
    shm_unlink(SHM_NAME);

    return 0;
}