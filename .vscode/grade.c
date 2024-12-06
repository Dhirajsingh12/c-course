#include <stdio.h>

int main()
{
    char grade;
    int marks;
    printf("enter the marks\t:-");
    scanf("%d", &marks);
    if (marks <= 100 && marks >= 90)
    {
        grade = 'A';
        printf("%c",grade);
    }
    else if (marks <= 90 && marks >= 80)
    {
        grade = 'B';
        printf("%c",grade);
    }

    else if (marks <= 80 && marks >= 70)
    {
        grade = 'C';
        printf("%c",grade);
    }
    else if (marks <= 70 && marks >= 60)
    {
        grade = 'D';
        printf("%c",grade);
    }
    else
    {
        grade = 'f';
        printf("%c",grade);
    }

    return 0;
}