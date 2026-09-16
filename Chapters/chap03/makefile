main: prob01/main.o copy.o
	gcc -o main main.o copy.o
main.o: prob01/main.c copy.h
	gcc -c main.c
copy.o: prob01/copy.c
	gcc -c copy.c
