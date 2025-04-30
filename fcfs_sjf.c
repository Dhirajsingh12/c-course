#include <stdio.h>

#define MAX 10

// Function for First Come First Serve (FCFS)
void FCFS(int arrival[], int burst[], int n) {
    int completion[MAX], waiting[MAX], turnaround[MAX];
    completion[0] = arrival[0] + burst[0];

    for (int i = 1; i < n; i++) {
        completion[i] = (arrival[i] > completion[i - 1]) ? arrival[i] + burst[i] : completion[i - 1] + burst[i];
    }

    // Calculate waiting and turnaround times
    for (int i = 0; i < n; i++) {
        turnaround[i] = completion[i] - arrival[i];
        waiting[i] = turnaround[i] - burst[i];
    }

    printf("\nFirst Come First Serve (FCFS) Scheduling:\n");
    printf("Process\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, arrival[i], burst[i], completion[i], waiting[i], turnaround[i]);
    }
}

// Function for Shortest Job First (SJF) - Non-preemptive
void SJF(int arrival[], int burst[], int n) {
    int completion[MAX], waiting[MAX], turnaround[MAX], temp, shortest;
    int completed = 0, currentTime = 0;
    int flag[MAX] = {0};

    // Sort processes based on arrival time first
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arrival[i] > arrival[j]) {
                temp = arrival[i];
                arrival[i] = arrival[j];
                arrival[j] = temp;

                temp = burst[i];
                burst[i] = burst[j];
                burst[j] = temp;
            }
        }
    }

    // Process the jobs using SJF
    while (completed < n) {
        shortest = -1;
        for (int i = 0; i < n; i++) {
            if (arrival[i] <= currentTime && !flag[i]) {
                if (shortest == -1 || burst[i] < burst[shortest]) {
                    shortest = i;
                }
            }
        }

        if (shortest == -1) {
            currentTime++;
            continue;
        }

        currentTime += burst[shortest];
        completion[shortest] = currentTime;
        turnaround[shortest] = completion[shortest] - arrival[shortest];
        waiting[shortest] = turnaround[shortest] - burst[shortest];
        flag[shortest] = 1;
        completed++;
    }

    printf("\nShortest Job First (SJF) Scheduling:\n");
    printf("Process\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, arrival[i], burst[i], completion[i], waiting[i], turnaround[i]);
    }
}

// Function for Priority Scheduling (Non-preemptive)
void PriorityScheduling(int arrival[], int burst[], int priority[], int n) {
    int completion[MAX], waiting[MAX], turnaround[MAX], temp, highestPriority;
    int completed = 0, currentTime = 0;
    int flag[MAX] = {0};

    // Sort processes based on arrival time and then by priority
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arrival[i] > arrival[j] || (arrival[i] == arrival[j] && priority[i] > priority[j])) {
                temp = arrival[i];
                arrival[i] = arrival[j];
                arrival[j] = temp;

                temp = burst[i];
                burst[i] = burst[j];
                burst[j] = temp;

                temp = priority[i];
                priority[i] = priority[j];
                priority[j] = temp;
            }
        }
    }

    // Process the jobs using Priority Scheduling
    while (completed < n) {
        highestPriority = -1;
        for (int i = 0; i < n; i++) {
            if (arrival[i] <= currentTime && !flag[i]) {
                if (highestPriority == -1 || priority[i] < priority[highestPriority]) {
                    highestPriority = i;
                }
            }
        }

        if (highestPriority == -1) {
            currentTime++;
            continue;
        }

        currentTime += burst[highestPriority];
        completion[highestPriority] = currentTime;
        turnaround[highestPriority] = completion[highestPriority] - arrival[highestPriority];
        waiting[highestPriority] = turnaround[highestPriority] - burst[highestPriority];
        flag[highestPriority] = 1;
        completed++;
    }

    printf("\nPriority Scheduling:\n");
    printf("Process\tArrival Time\tBurst Time\tPriority\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, arrival[i], burst[i], priority[i], completion[i], waiting[i], turnaround[i]);
    }
}

// Main Function with switch-case
int main() {
    int arrival[MAX], burst[MAX], priority[MAX], n, choice;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Get input for arrival time, burst time and priority
    printf("Enter arrival times:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &arrival[i]);
    }

    printf("Enter burst times:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &burst[i]);
    }

    printf("Enter priorities (lower value indicates higher priority):\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &priority[i]);
    }

    // Display menu for scheduling algorithms
    printf("\nChoose the scheduling algorithm:\n");
    printf("1. FCFS (First-Come, First-Served)\n");
    printf("2. SJF (Shortest Job First)\n");
    printf("3. Priority Scheduling\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    // Use switch-case to choose scheduling algorithm
    switch (choice) {
        case 1:
            FCFS(arrival, burst, n);
            break;
        case 2:
            SJF(arrival, burst, n);
            break;
        case 3:
            PriorityScheduling(arrival, burst, priority, n);
            break;
        default:
            printf("Invalid choice!\n");
    }

    return 0;
}