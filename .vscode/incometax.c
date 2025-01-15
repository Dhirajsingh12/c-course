#include <stdio.h>

void main()
{
    float income, tax =0;
    printf("enter your income\t");
    scanf("%f", &income);
    if (income < 250000)
    {
        tax = 0;
    }
    else if (tax > 250000 && tax < 500000)
    {
        tax = 0.05 * (income - 250000);
       
    }
    else if (tax > 500000 && tax < 1000000)
    {
        tax = 0.05* (500000-250000)+ 0.2*(income-1000000);
       
    }
    else
    {
       
         tax = 0.05* (500000-250000)+ 0.2*(1000000-500000)+0.5*(income-1000000);
         printf("total your tax=%f",&tax);
    }
    
}
