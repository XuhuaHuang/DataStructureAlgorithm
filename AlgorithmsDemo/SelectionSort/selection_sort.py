# Topic: Selection sort algorithm implementation and demostration
#
# To run the Python file:
# $ python --version
# $ python .\selection_sort.py
# 
# To import the function from other Python source code:
# from selection_sort.py import selection_sort
#
# Author: Xuhua Huang
# Last updated: Nov 13, 2021
# Created on: Nov 13, 2021

from typing import Any


def selection_sort(_list: list[Any]):
    # Time complexity: O(n^2)
    # suppose that the first element is the smallest
    smallest_num_index: int = 0
    # loop through the list
    # for each iteration, find the index of the smaller number
    for i in range(len(_list)):
        smallest_num_index = i;
        for j in range(i+1, len(_list), 1):
            if _list[j] < _list[smallest_num_index]:
                smallest_num_index = j
        # if there is indeed a smaller number
        # use the updated index to swap the elements
        if smallest_num_index != i:
            _list[i], _list[smallest_num_index] = _list[smallest_num_index], _list[i]
    # add empty return statement for consistency
    return



def main():
    to_sort_int: list[int] = [4, 2, 7, 1, 3]
    print("Before calling selection_sort(): ", to_sort_int)
    selection_sort(to_sort_int)
    print("After calling selction_sort(): ", to_sort_int)

    to_sort_char: list[str] = ['a', 's', 'd', 'f', 'b', 'c', 'e']
    print("Before calling selection_sort(): ", to_sort_char)
    selection_sort(to_sort_char)
    print("After calling selection_sort(): ", to_sort_char)


if __name__ == '__main__':
    main()