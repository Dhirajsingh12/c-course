#include<stdio.h>

int main(){
     int n=20;
     for (int i = 0; i < n; i++)
     {
        if (i==6)
        {
            continue;
        }
        printf("%d\n",i);
     }
     
    return 0;
}