#include <stdio.h>

int f(int x) 
int y;
{
    return x + y;
}

int g(int x) {
    return x * y;
}

int main() {
    int i, x = 5, y = 10;

    for(i = 1; i <= 2; i++) {
        y = y + f(x) + g(x);
        printf("%d\n", y);
    }

    return 0;
}
