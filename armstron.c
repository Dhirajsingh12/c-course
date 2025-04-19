#include <stdio.h>
#include <math.h>

int main() {
    int num, originalNum, remainder, result = 0, n = 0;

    printf("Enter a number: ");
    scanf("%d", &num);

    originalNum = num;


    for (int temp = num; temp != 0; temp /= 10) {
        n++;
    }

    for (int temp = num; temp != 0; temp /= 10) {
        remainder = temp % 10;
        result += (int)(pow(remainder, n) + 0.5);  
    }

    if (result == originalNum)
        printf("%d is an Armstrong number.\n", originalNum);
    else
        printf("%d is not an Armstrong number.\n", originalNum);

    return 0;
}
