#include <stdio.h>

int main() {
    int rows = 5;

    for (int i = 1; i <= rows; i++) {
        int spaces, stars;
        
        if (i == 1 || i == 5) {
            spaces = 4;
            stars = 1;
        } else if (i == 2 || i == 4) {
            spaces = 3;
            stars = 2;
        } else if (i == 3) {
            spaces = 2;
            stars = 3;
        }

        for (int s = 1; s <= spaces; s++) {
            printf(" ");
        }

        for (int s = 1; s <= stars; s++) {
            printf("* ");
        }

        printf("\n"); 
    }

    return 0;
}
