# Topic: Bubble sort algorithm implementation and demostration
#
# To run the Python file:
# $ python --version
# $ python .\bubble_sort.py
# 
# To import the function from other Python source code:
# from bubble_sort.py import bubble_sort
#
# Author: Xuhua Huang
# Last updated: Nov 13, 2021
# Created on: Nov 13, 2021


from typing import Any

def bubble_sort(list: list[Any]):
    unsorted_until_index: int = len(list) - 1;
    sorted: bool = False;

    while not sorted:
        sorted = True
        for i in range(unsorted_until_index):
            if list[i] > list[i+1]:
                sorted = False;
                list[i], list[i+1] = list[i+1], list[i]
        unsorted_until_index -= 1


def main():
    arr: list[int] = [65, 55, 45, 35, 25, 15, 10]
    bubble_sort(arr)
    print(arr)


if __name__ == '__main__':
    main()