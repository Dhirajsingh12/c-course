#include <stdio.h>
int main()
{
    int AT[10], BT[10], WT[10], TT[10], ST[10], TempAT[10], Order[10], n, location=0, loc, small, i, j, Start;
    int TWT, TTT;
    float Avg_WT, Avg_TT;
    
    printf("Enter number of the processes:\n");
    scanf("%d", &n);
    
    printf("Enter Arrival time and Burst time of the process\n");
    printf("\tAT\tBT\n");
    for(i = 0; i < n; i++)
    {
        printf("P%d: ", i);
        scanf("%d%d", &AT[i], &BT[i]);
    }

    for(i = 0; i < n; i++)
        TempAT[i] = AT[i];

    for(i = 0; i < n; i++)
    {
        small = 10000;
        for(j = 0; j < n; j++)
        {
            if(small > TempAT[j])
            {
                small = TempAT[j];
                loc = j;
            }
        }
        Order[location++] = loc;
        TempAT[loc] = 10000; // Mark as visited
    }

    printf("Order of Execution is:\n");
    for(i = 0; i < n; i++)
    {
        printf("P%d\t", Order[i]);
    }

    Start = AT[Order[0]];
    for(i = 0; i < n; i++)
    {
        if(Start < AT[Order[i]])
            Start = AT[Order[i]];
        ST[Order[i]] = Start;
        Start = Start + BT[Order[i]];
    }

    printf("\nStart to End Time of Each Process is:\n");
    for(i = 0; i < n; i++)
    {
        printf("P%d : %d to %d\n", i, ST[i], ST[i] + BT[i]);
    }

    TWT = 0;
    TTT = 0;
    for(i = 0; i < n; i++)
    {
        WT[i] = ST[i] - AT[i];
        TWT += WT[i];
        TT[i] = ST[i] + BT[i] - AT[i];
        TTT += TT[i];
    }

    Avg_WT = (float)TWT / n;
    Avg_TT = (float)TTT / n;

    printf("\nProcess\tWaiting Time\tTurnaround Time\n");
    for(i = 0; i < n; i++)
    {
        printf("P%d\t\t%d\t\t%d\n", i, WT[i], TT[i]);
    }

    printf("\nAverage waiting time is: %.2f\n", Avg_WT);
    printf("Average turnaround time is: %.2f\n", Avg_TT);

    return 0;
}
