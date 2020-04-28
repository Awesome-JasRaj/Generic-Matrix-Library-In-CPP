matrix: execute.o main.o
	g++ execute.o main.o -o matrix
execute.o: execute.cpp matrix_library.h 
	g++ -c execute.cpp
main.o: execute.cpp matrix_library.h
	g++ -c main.cpp
