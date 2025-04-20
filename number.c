#include <stdio.h>

int main()
{
    int a, b;
    printf("Enter the first number: ");
    scanf("%d", &a);

    printf("Enter the second number: ");
    scanf("%d", &b);

    int i = a; 
    while (i <= b)
    {
        if (i % 3 == 0)
        {
            printf("%d ", i);
        }
        i = i + 1;
    }

    return 0;
}
