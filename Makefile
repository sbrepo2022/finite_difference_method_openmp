all:
	g++ -c main.cpp -o build/main.o -fopenmp
	g++ -c single_thread.cpp -o build/single_thread.o -fopenmp
	g++ -c multi_thread.cpp -o build/multi_thread.o -fopenmp
	g++ build/main.o build/single_thread.o build/multi_thread.o -o main -fopenmp -lpthread