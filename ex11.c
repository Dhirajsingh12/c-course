#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// #include <sys/ipc.h>
// #include <sys/shm.h>
// #include <sys/sem.h>

#define SIZE 5
#define PRODUCE_COUNT 10

typedef struct {
    int buffer[SIZE];
    int in;
    int out;
} SharedBuffer;

// Semaphore index
enum { EMPTY = 0, FULL = 1, MUTEX = 2 };

// Semaphore operations
void sem_wait(int semid, int semnum) {
    struct sembuf sb = {semnum, -1, 0};
    semop(semid, &sb, 1);
}

void sem_signal(int semid, int semnum) {
    struct sembuf sb = {semnum, +1, 0};
    semop(semid, &sb, 1);
}

int main() {
    key_t shmkey = ftok("shmfile",65);
    int shmid = shmget(shmkey, sizeof(SharedBuffer), 0666|IPC_CREAT);
    SharedBuffer* sb = (SharedBuffer*) shmat(shmid, NULL, 0);

    sb->in = 0;
    sb->out = 0;

    key_t semkey = ftok("semfile",75);
    int semid = semget(semkey, 3, 0666|IPC_CREAT);

    // Initialize semaphores: empty = SIZE, full = 0, mutex = 1
    semctl(semid, EMPTY, SETVAL, SIZE);
    semctl(semid, FULL, SETVAL, 0);
    semctl(semid, MUTEX, SETVAL, 1);

    pid_t pid = fork();

    if (pid == 0) {
        // Producer
        for (int i = 1; i <= PRODUCE_COUNT; i++) {
            sem_wait(semid, EMPTY);
            sem_wait(semid, MUTEX);

            sb->buffer[sb->in] = i;
            printf("Produced: %d\n", i);
            sb->in = (sb->in + 1) % SIZE;

            sem_signal(semid, MUTEX);
            sem_signal(semid, FULL);
            sleep(1);
        }
    } else {
        // Consumer
        for (int i = 1; i <= PRODUCE_COUNT; i++) {
            sem_wait(semid, FULL);
            sem_wait(semid, MUTEX);

            int item = sb->buffer[sb->out];
            printf("Consumed: %d\n", item);
            sb->out = (sb->out + 1) % SIZE;

            sem_signal(semid, MUTEX);
            sem_signal(semid, EMPTY);
            sleep(2);
        }

        wait(NULL);

        // Cleanup
        shmdt(sb);
        shmctl(shmid, IPC_RMID, NULL);
        semctl(semid, 0, IPC_RMID);
    }

    return 0;
}
