/**
 * @file selection_sort.c
 * @author Xuhua Huang (xuhuahuang0412@gmail.com)
 * @brief Selection sort algorithm implementation and demonstration in C.
 * Time complexity: o(N^2)
 * Caution: facing random poitner glitches. Waiting to implement in C++.
 * 
 * To compile and run on Windows with Makefile:
 * $ mingw32-make
 * $ ./selectionsort
 * 
 * @version 0.1
 * @date 2021-11-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdio.h>
#include <stdlib.h>

void selection_sort(int* arr) {
    int smallest_num_index = 0; /* Suppose the first element of the array is the smallest. */
    
    for (int i = 0; i < sizeof(arr); i++) {
        smallest_num_index = i; /* Update the index during each iteration. */
        /* Loop through the rest of the array. */
        for (int j = i; j < sizeof(arr); j++) {
            if (arr[j] < arr[smallest_num_index]) {
                smallest_num_index = j;
            }
        }
        /**
         * @brief If a smaller number is found, i.e.
         * variable `smallest_num_index` has been updated
         */
        if (smallest_num_index != i) {
            /* Swap the elements. */
            int temp = arr[i];
            arr[i] = arr[smallest_num_index];
            arr[smallest_num_index] = temp;
        }
    }

    return;
}

void print_array(int* arr) {
    printf("{ ");
    for (int i = 0; i < sizeof(arr); i++) {
        printf("%d ", arr[i]);
    }
    printf("}\n");
}

int main(void) {
    int to_sort[] = { 4, 2, 7, 1, 3 };
    print_array(to_sort);

    selection_sort(to_sort);
    print_array(to_sort);

    system("pause");
    return 0;
}