#include <stdio.h>

#define MAX 100

struct Process {
    int pid;
    int bt;   
    int at;  
    int prio; 
};

void sortByBurstTime(struct Process p[], int n) {
    struct Process temp;
    for(int i=0; i<n-1; i++) {
        for(int j=0; j<n-i-1; j++) {
            if(p[j].bt > p[j+1].bt) {
                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
}

void sortByPriority(struct Process p[], int n) {
    struct Process temp;
    for(int i=0; i<n-1; i++) {
        for(int j=0; j<n-i-1; j++) {
            if(p[j].prio > p[j+1].prio) {
                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
}

void sortByArrivalTime(struct Process p[], int n) {
    struct Process temp;
    for(int i=0; i<n-1; i++) {
        for(int j=0; j<n-i-1; j++) {
            if(p[j].at > p[j+1].at) {
                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
}

void display(struct Process p[], int n) {
    printf("\nExecution Order:\n");
    for(int i=0; i<n; i++) {
        printf("P%d ", p[i].pid);
    }
    printf("\n");
}

void multiLevelQueue(struct Process p[], int n) {
    printf("\n--- Multi-Level Queue Scheduling ---\n");

    struct Process q1[MAX], q2[MAX];
    int n1 = 0, n2 = 0;

    for (int i = 0; i < n; i++) {
        if (p[i].prio <= 3) {
            q1[n1++] = p[i]; 
        } else {
            q2[n2++] = p[i]; 
        }
    }

    printf("\nQueue 1 (High Priority - FCFS):\n");
    sortByArrivalTime(q1, n1);
    display(q1, n1);

    printf("\nQueue 2 (Low Priority - SJF):\n");
    sortByBurstTime(q2, n2);
    display(q2, n2);
}

int main() {
    int n, choice;
    struct Process p[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(int i=0; i<n; i++) {
        p[i].pid = i+1;
        printf("Enter burst time, arrival time and priority for Process %d: ", i+1);
        scanf("%d %d %d", &p[i].bt, &p[i].at, &p[i].prio);
    }

    printf("\nSelect CPU Scheduling Policy:\n");
    printf("1. Shortest Job First (SJF)\n");
    printf("2. Priority Scheduling\n");
    printf("3. First Come First Serve (FCFS)\n");
    printf("4. Multi-Level Queue Scheduling\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch(choice) {
        case 1:
            sortByBurstTime(p, n);
            printf("\n--- Shortest Job First ---\n");
            display(p, n);
            break;
        case 2:
            sortByPriority(p, n);
            printf("\n--- Priority Scheduling ---\n");
            display(p, n);
            break;
        case 3:
            sortByArrivalTime(p, n);
            printf("\n--- First Come First Serve ---\n");
            display(p, n);
            break;
        case 4:
            multiLevelQueue(p, n);
            break;
        default:
            printf("Invalid choice!\n");
    }

    return 1;
}
