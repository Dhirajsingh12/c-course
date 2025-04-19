#include <stdio.h>

int main() {
    int a, b;
    int count = 0;

    printf("Enter two numbers (a and b): ");
    scanf("%d %d", &a, &b);

    int newnum = a + 1;

    do {
        if (newnum >= b) 
            break;

        printf("%d\n", newnum);
        count++;
        newnum++;
    } while (1);

    printf("Total numbers printed: %d\n", count);

    return 0;
}
