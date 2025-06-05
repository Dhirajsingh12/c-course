#include <stdio.h>

#define MAX 10

int main() {
    int n, m; // n = number of processes, m = number of resource types
    int alloc[MAX][MAX], max[MAX][MAX], need[MAX][MAX], avail[MAX];
    int finish[MAX] = {0}, safeSeq[MAX];
    int i, j, k;

    // Input number of processes and resources
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    // Input Allocation Matrix
    printf("Enter Allocation Matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    // Input Max Matrix
    printf("Enter Maximum Matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
            need[i][j] = max[i][j] - alloc[i][j]; // Calculate Need
        }
    }

    // Input Available resources
    printf("Enter Available Resources:\n");
    for (j = 0; j < m; j++) {
        scanf("%d", &avail[j]);
    }

    // Safety Algorithm
    int count = 0;
    while (count < n) {
        int found = 0;
        for (i = 0; i < n; i++) {
            if (!finish[i]) {
                int canExecute = 1;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]) {
                        canExecute = 0;
                        break;
                    }
                }

                if (canExecute) {
                    for (k = 0; k < m; k++) {
                        avail[k] += alloc[i][k];
                    }
                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (!found) {
            printf("\n❌ System is not in a safe state (Deadlock may occur).\n");
            return 0;
        }
    }

    // Safe Sequence
    printf("\n✅ System is in a safe state.\nSafe sequence: ");
    for (i = 0; i < n; i++) {
        printf("P%d ", safeSeq[i]);
    }
    printf("\n");

    return 0;
}
