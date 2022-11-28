/**
 * @file bubble_sort.c
 * @author Xuhua Huang (xuhuahuang0412@gmail.com)
 * @brief Demonstration of bubble sort algorithm in C.
 * Time complexity: O(n)
 * @version 0.1
 * @date 2021-11-12
 * 
 * To compile and run on Windows:
 * $ mingw32-make
 * $ ./bubblesort
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void bubble_sort(int* arr) {
    int unsorted_until_index = sizeof(arr) - 1;             /* Minus the extra null character. */
    printf("Size of the pointer: %d.\n", sizeof(arr));
    bool sorted = false;

    while (!sorted) {
        sorted = true;
        /* Loop through the rest of the array. */
        for (int i = 0; i < unsorted_until_index; i++) {
            /* Compare the elements and determine whether to swap. */
            if (arr[i] > arr[i+1]) {
                sorted = false;
                /* Swap the elements. */
                int temp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = temp;
            }
        }
        unsorted_until_index--;
    }

    return; /* Empty return statement for consistency. */
}

int main(void) {
    int to_sort[] = { 65, 55, 45, 35, 25, 15, 10, 5 };
    printf("Size of the array: %d.\n", sizeof(to_sort)/sizeof(to_sort[0]));
    bubble_sort(to_sort);

    for(int i = 0; i < sizeof(to_sort)/sizeof(to_sort[0]); ++i) {
        printf("%d ", to_sort[i]);
    }
    printf("\n");
    printf("Done.\n");

    system("pause");
    return 0;
}