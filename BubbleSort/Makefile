.bubblesort: all clean
all: bubblesort
bubblesort: bubble_sort.o
	gcc -o bubblesort bubble_sort.o
bubble_sort.o: bubble_sort.c
	gcc -c bubble_sort.c
clean:
	rm -f bubble_sort.o bubblesort.exe