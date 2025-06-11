#include <windows.h>
#include <stdio.h>

#define BUFFER_SIZE 5
#define MAX_ITEMS 20

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

int count = 0;

HANDLE empty, full, mutex;

DWORD WINAPI producer(LPVOID param) {
    int item;
    for (int i = 0; i < MAX_ITEMS; i++) {
        item = rand() % 100;

        WaitForSingleObject(empty, INFINITE);
        WaitForSingleObject(mutex, INFINITE);

        buffer[in] = item;
        printf("Producer produced item %d at position %d\n", item, in);
        in = (in + 1) % BUFFER_SIZE;

        ReleaseMutex(mutex);
        ReleaseSemaphore(full, 1, NULL);

        Sleep(rand() % 1000);
    }
    return 0;
}

DWORD WINAPI consumer(LPVOID param) {
    int item;
    for (int i = 0; i < MAX_ITEMS; i++) {
        WaitForSingleObject(full, INFINITE);
        WaitForSingleObject(mutex, INFINITE);

        item = buffer[out];
        printf("Consumer consumed item %d from position %d\n", item, out);
        out = (out + 1) % BUFFER_SIZE;

        ReleaseMutex(mutex);
        ReleaseSemaphore(empty, 1, NULL);

        Sleep(rand() % 1500);
    }
    return 0;
}

int main() {
    HANDLE hProducer, hConsumer;

    empty = CreateSemaphore(NULL, BUFFER_SIZE, BUFFER_SIZE, NULL);
    full = CreateSemaphore(NULL, 0, BUFFER_SIZE, NULL);
    mutex = CreateMutex(NULL, FALSE, NULL);

    hProducer = CreateThread(NULL, 0, producer, NULL, 0, NULL);
    hConsumer = CreateThread(NULL, 0, consumer, NULL, 0, NULL);

    WaitForSingleObject(hProducer, INFINITE);
    WaitForSingleObject(hConsumer, INFINITE);

    CloseHandle(empty);
    CloseHandle(full);
    CloseHandle(mutex);
    CloseHandle(hProducer);
    CloseHandle(hConsumer);

    return 0;
}
