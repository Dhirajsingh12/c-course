#include<stdio.h>

int main(){
     float selsious;
     float farenhight;
     printf("enter the selsious\n:-");
     scanf("%f",&selsious);
     farenhight=((9.0/5.0)*selsious) + 32;
     printf("the value of farenhight: %f",farenhight);
    return 0;
}