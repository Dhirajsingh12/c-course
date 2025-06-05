#include <stdio.h>
#include <stdlib.h> // for abs()

int compactMemory(int memory[], int size) {
    int writeIndex = 0;
    int totalMovement = 0;

    for (int readIndex = 0; readIndex < size; readIndex++) {
        if (memory[readIndex] != 0) {
            if (readIndex != writeIndex) {
                memory[writeIndex] = memory[readIndex];
                totalMovement += abs(readIndex - writeIndex);
            }
            writeIndex++;
        }
    }

    // Fill remaining memory with 0s
    for (int i = writeIndex; i < size; i++) {
        memory[i] = 0;
    }

    return totalMovement;
}

void printMemory(int memory[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", memory[i]);
    }
    printf("\n");
}

int main() {
    int memory[] = {1, 0, 2, 0, 3, 0, 4, 0, 0};
    int size = sizeof(memory) / sizeof(memory[0]);

    printf("Original Memory: ");
    printMemory(memory, size);

    int totalMovement = compactMemory(memory, size);

    printf("Compacted Memory: ");
    printMemory(memory, size);
    printf("Total Data Movement: %d\n", totalMovement);

    return 0;
}
