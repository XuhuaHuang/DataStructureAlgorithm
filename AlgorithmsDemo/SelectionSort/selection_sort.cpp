/**
 * @file selection_sort.cpp
 * @author Xuhua Huang (xuhuahuang0412@gmail.com)
 * @brief Selection sort algorithm implementation and demonstration in C++.
 * Time complexity: o(N^2)
 * Thanks to encapsulation of array in C++, this version is working.
 * Implementation in C using raw pointer is facing stack samshing issue.
 * 
 * @version 1.0
 * @date 2021-11-15
 * 
 * To compile and run the file on Windows with g++:
 * $ g++ -o selectionsortcpp selection_sort.cpp
 * $ ./selectionsortcpp
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <iostream>
#include <stdlib.h>
#include <vector>

void selection_sort(std::vector<int>& arr) {
    int smallest_num_index = 0;
    for (int i = 0; i < arr.size(); ++i) {
        smallest_num_index = i;
        for (int j = i + 1; j < arr.size(); ++j) {
            if (arr[j] < arr[smallest_num_index]) {
                smallest_num_index = j;
            }
        }
        if (smallest_num_index != i) {
            int temp = arr[i];
            arr[i] = arr[smallest_num_index];
            arr[smallest_num_index] = temp;
        }
    }
    /* Return statement for consistency of the control flow. */
    return;
}

void print_array(const std::vector<int>& arr) {
    std::cout << "{ ";
    for (int i = 0; i < arr.size(); ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << "}" << std::endl;
    return;
}

int main(void) {
    std::vector<int> to_sort = { 4, 2, 7, 1, 3, 9 };
    
    std::cout << "Before sorting: ";
    print_array(to_sort);

    std::cout << "Sorting...\n";
    selection_sort(to_sort);

    std::cout << "After sorting: ";
    print_array(to_sort);
    
    system("pause");
    return 0;
}