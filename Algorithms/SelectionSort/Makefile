.selectionsort: all clean
all: selectionsort
selectionsort: selection_sort.o
	gcc -o selectionsort selection_sort.o
selection_sort.o: selection_sort.c
	gcc -c selection_sort.c
clean:
	rm -f selection_sort.o selectionsort.exe