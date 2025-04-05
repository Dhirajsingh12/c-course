#include <stdio.h>

int f(int x) {
    return x + 1;
}

int g(int x) {
    return x * 2;
}

int main() {
    int i, x = 5, y = 10;

    for(i = 1; i <= 2; i++) {
        y = y + f(x) + g(x);
        printf("%d\n", y);
    }

    return 0;
}
