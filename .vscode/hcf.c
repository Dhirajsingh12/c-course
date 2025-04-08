#include <stdio.h>

int main() {
    int num1;
    int num2;
    int a;
    int b; 
    int temp;
    printf("Enter two positive number: ");
    scanf("%d %d", &num1, &num2);
    a = num1;
    b = num2;
    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }

    printf("GCF of %d and %d is: %d\n", num1, num2, a);

    return 0;
}
