#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10

int adj[MAX][MAX]; // Adjacency matrix for RAG
int n = 0;          // Total nodes (processes + resources)

// Mapping: Process P0 = 0, P1 = 1...; Resource R0 = MAX/2, R1 = MAX/2 + 1...
int processOffset = 0;
int resourceOffset = MAX / 2;

// Function to add request edge (P → R)
void requestResource(int process, int resource) {
    adj[processOffset + process][resourceOffset + resource] = 1;
}

// Function to assign resource (R → P)
void assignResource(int resource, int process) {
    adj[resourceOffset + resource][processOffset + process] = 1;
}

// Function to print adjacency matrix
void printRAG(int totalProcesses, int totalResources) {
    printf("\nResource Allocation Graph (Adjacency Matrix):\n");
    printf("    ");
    for (int i = 0; i < totalProcesses; i++) {
        printf("P%d ", i);
    }
    for (int i = 0; i < totalResources; i++) {
        printf("R%d ", i);
    }
    printf("\n");

    for (int i = 0; i < totalProcesses + totalResources; i++) {
        if (i < totalProcesses)
            printf("P%d: ", i);
        else
            printf("R%d: ", i - totalProcesses);

        for (int j = 0; j < totalProcesses + totalResources; j++) {
            printf(" %d ", adj[i][j]);
        }
        printf("\n");
    }
}

// Optional: Simple cycle detection (DFS)
int visited[MAX], recStack[MAX];

int isCyclicUtil(int v, int totalNodes) {
    if (!visited[v]) {
        visited[v] = 1;
        recStack[v] = 1;

        for (int i = 0; i < totalNodes; i++) {
            if (adj[v][i]) {
                if (!visited[i] && isCyclicUtil(i, totalNodes))
                    return 1;
                else if (recStack[i])
                    return 1;
            }
        }
    }
    recStack[v] = 0;
    return 0;
}

int detectDeadlock(int totalNodes) {
    memset(visited, 0, sizeof(visited));
    memset(recStack, 0, sizeof(recStack));

    for (int i = 0; i < totalNodes; i++) {
        if (isCyclicUtil(i, totalNodes))
            return 1;
    }
    return 0;
}

int main() {
    int totalProcesses = 3;
    int totalResources = 2;

    // Sample: P0 requests R0, R0 assigned to P1, P1 requests R1, R1 assigned to P0 → Deadlock
    requestResource(0, 0); // P0 → R0
    assignResource(0, 1);  // R0 → P1
    requestResource(1, 1); // P1 → R1
    assignResource(1, 0);  // R1 → P0

    printRAG(totalProcesses, totalResources);

    if (detectDeadlock(totalProcesses + totalResources))
        printf("\n Deadlock Detected!\n");
    else
        printf("\n✅ No Deadlock Detected.\n");

    return 0;
}
