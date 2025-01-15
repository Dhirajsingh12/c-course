#include<stdio.h>

int main(){
     int a=70,b=4,c=1,d=50;
     if (a>b && a>c && a>d)
     {
        printf("greatest number is %d",a);  
     }
     else if (b>a && b>c && b>d)
     {
        printf("greatest number %d",b);
     }
     else if (c>a && c>b && c>d)
     {
        printf("greatest number is %d",c);
     }
     else if (d>a && d>b && d>c)
     {
        printf("greatest number is %d",d);
     }
     
    return 0;
}