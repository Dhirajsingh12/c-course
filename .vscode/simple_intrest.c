#include<stdio.h>

int main(){
     float p;
     float r;
     int t;
     float si;
     printf("enter the principul\n");
     scanf("%f",&p);
     printf("enter the rate\n");
     scanf("%f",&r);
     printf("enter the time\n");
     scanf("%d",&t);
     si=(p*r*t)/100;
     printf("simple intrest %f",si);

    return 1;
}