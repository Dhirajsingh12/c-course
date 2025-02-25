#include <stdio.h>

int main()
{

    // taking an integer variable
    int m = 100;

    // pointer variable ptr that stores
    // the address of variable m
    int *ptr = &m;

    // printing the value of variable m
    printf("The Value of Variable m is: %d\n", m);

    // printing the memory address of variable m
    // in hexadecimal format
    printf("The Memory Address of Variable m is: %p\n", &m);

    // printing the value of ptr i.e.
    // printing the memory address of variable m
    // in hexadecimal format using pointer variable
    printf("The Memory Address of Variable m is using ptr: %p\n", ptr);

    return 0;
}
