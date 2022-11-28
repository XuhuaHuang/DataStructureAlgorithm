# Topic: Insertion sort algorithm implementation and demonstration in Python.
# Optimistic tuning: the best and worst cases are less likely to happen in general.
# To run the Python file:
# $ python --version
# $ python .\insertion_sort.py
# 
# To import the function from other Python source code:
# from insertion_sort.py import insertion_sort
#
# Author: Xuhua Huang
# Last updated: Nov 16, 2021
# Created on: Nov 16, 2021

from typing import Any


def insertion_sort(_list: list[Any]):
    # Algorithm time complexity: O(N^2)
    # Pseudo code:
    # Pick the first element (cursor), loop through the rest of the list
    # Compare the first element with the rest of the list
    # Move the bigger element to the right hand side
    # Insert the element to the empty slot to the left
    index: int = 0
    for index in range(1, len(_list)):
        position: int = index
        temp_value: int = _list[index]
        # Launch an while loop to move elements around
        # to find an empty slot
        while position > 0 and _list[position-1] > temp_value:
            _list[position] = _list[position-1]  # Move all smaller elements to the right
            position -= 1
        _list[position] = temp_value  # Insert the temporary value to the empty slot
    # Add empty statement for consistency
    return


def main():
    to_sort: list[int] = [4, 2, 7, 1, 3, 8]
    print("Before sorting: ", to_sort)

    print("Sorting...")
    insertion_sort(to_sort)

    print("After sorting: ", to_sort)


if __name__ == '__main__':
    main()