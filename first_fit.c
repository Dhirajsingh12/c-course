#include <stdio.h>
#include <stdbool.h>

#define MAX_BLOCKS 100
#define MAX_PROCESSES 100

int main() {
    int blockSize[MAX_BLOCKS], processSize[MAX_PROCESSES];
    int blockCount, processCount;
    int allocation[MAX_PROCESSES];

    printf("Enter number of memory blocks: ");
    scanf("%d", &blockCount);

    printf("Enter sizes of memory blocks:\n");
    for (int i = 0; i < blockCount; i++) {
        scanf("%d", &blockSize[i]);
    }

    printf("Enter number of processes: ");
    scanf("%d", &processCount);

    printf("Enter sizes of processes:\n");
    for (int i = 0; i < processCount; i++) {
        scanf("%d", &processSize[i]);
        allocation[i] = -1; 
    }

    // First Fit Allocation
    for (int i = 0; i < processCount; i++) {
        for (int j = 0; j < blockCount; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }

    printf("\nProcess No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < processCount; i++) {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }

    return 0;
}
