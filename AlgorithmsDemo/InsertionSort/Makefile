.insertionsort: all clean
all: insertionsort
insertionsort: insertion_sort.o
	g++ -o insertionsort insertion_sort.o
insertion_sort.o: insertion_sort.cpp
	g++ -c insertion_sort.cpp -std=c++11
clean:
	rm -f insertion_sort.o insertionsort.exe