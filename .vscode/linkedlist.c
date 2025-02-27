#include <stdio.h>
int main() {
    int n, i, search, found = -1;

    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter %d elements:\n", n);
    for (i = 0; i < n; i++) {
        printf("Element %d: ", i + 1);
        scanf("%d", &arr[i]);
    }
    printf("Enter the item to search: ");
    scanf("%d", &search);
    for (i = 0; i < n; i++) {
        if (arr[i] == search) {
            found = i; 
            break;
        }
    }
    if (found != -1) {
        printf("Item %d found at location %d.\n", search, found + 1);
    } else {
        printf("Item %d not found in the array.\n", search);
    }

    return 0;
}
