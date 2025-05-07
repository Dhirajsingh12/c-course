#include <stdio.h>
#include <stdbool.h>

#define MAX_BLOCKS 100
#define MAX_PROCESSES 100

int blocks[MAX_BLOCKS], blockSize;
int processes[MAX_PROCESSES], processSize;
int lastAllocatedIndex = 0; // Used for Next Fit

void resetBlocks(int original[]) {
    for (int i = 0; i < blockSize; i++) {
        blocks[i] = original[i];
    }
}

void firstFit() {
    printf("\nFirst Fit Allocation:\n");
    for (int i = 0; i < processSize; i++) {
        bool allocated = false;
        for (int j = 0; j < blockSize; j++) {
            if (blocks[j] >= processes[i]) {
                printf("Process %d -> Block %d\n", i + 1, j + 1);
                blocks[j] -= processes[i];
                allocated = true;
                break;
            }
        }
        if (!allocated)
            printf("Process %d -> Not Allocated\n", i + 1);
    }
}

void bestFit() {
    printf("\nBest Fit Allocation:\n");
    for (int i = 0; i < processSize; i++) {
        int bestIdx = -1;
        for (int j = 0; j < blockSize; j++) {
            if (blocks[j] >= processes[i]) {
                if (bestIdx == -1 || blocks[j] < blocks[bestIdx])
                    bestIdx = j;
            }
        }
        if (bestIdx != -1) {
            printf("Process %d -> Block %d\n", i + 1, bestIdx + 1);
            blocks[bestIdx] -= processes[i];
        } else {
            printf("Process %d -> Not Allocated\n", i + 1);
        }
    }
}

void worstFit() {
    printf("\nWorst Fit Allocation:\n");
    for (int i = 0; i < processSize; i++) {
        int worstIdx = -1;
        for (int j = 0; j < blockSize; j++) {
            if (blocks[j] >= processes[i]) {
                if (worstIdx == -1 || blocks[j] > blocks[worstIdx])
                    worstIdx = j;
            }
        }
        if (worstIdx != -1) {
            printf("Process %d -> Block %d\n", i + 1, worstIdx + 1);
            blocks[worstIdx] -= processes[i];
        } else {
            printf("Process %d -> Not Allocated\n", i + 1);
        }
    }
}

void nextFit() {
    printf("\nNext Fit Allocation:\n");
    int index = lastAllocatedIndex;
    for (int i = 0; i < processSize; i++) {
        bool allocated = false;
        int count = 0;
        while (count < blockSize) {
            if (blocks[index] >= processes[i]) {
                printf("Process %d -> Block %d\n", i + 1, index + 1);
                blocks[index] -= processes[i];
                allocated = true;
                break;
            }
            index = (index + 1) % blockSize;
            count++;
        }
        if (!allocated)
            printf("Process %d -> Not Allocated\n", i + 1);
    }
    lastAllocatedIndex = index;
}

int main() {
    int originalBlocks[MAX_BLOCKS];

    printf("Enter number of memory blocks: ");
    scanf("%d", &blockSize);
    printf("Enter sizes of memory blocks:\n");
    for (int i = 0; i < blockSize; i++) {
        scanf("%d", &blocks[i]);
        originalBlocks[i] = blocks[i];
    }

    printf("Enter number of processes: ");
    scanf("%d", &processSize);
    printf("Enter memory required for each process:\n");
    for (int i = 0; i < processSize; i++) {
        scanf("%d", &processes[i]);
    }

    resetBlocks(originalBlocks);
    firstFit();

    resetBlocks(originalBlocks);
    bestFit();

    resetBlocks(originalBlocks);
    worstFit();

    resetBlocks(originalBlocks);
    nextFit();

    return 0;
}
