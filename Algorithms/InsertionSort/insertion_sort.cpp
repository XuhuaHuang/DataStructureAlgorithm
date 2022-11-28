/**
 * @file insertion_sort.cpp
 * @author Xuhua Huang (xuhuahuang0412@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-16
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <iostream>
#include <stdlib.h>
#include <vector>

void insertion_sort(std::vector<int>& arr) {

    /* Empty return statement for consistency of the control flow. */
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
    
    system("pause");
    return 0;
}