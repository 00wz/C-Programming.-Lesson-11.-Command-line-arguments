all: clean main

main: main.o temp_functions.o
	gcc -o main main.o temp_functions.o

main.o: main.c
	gcc -c -o main.o main.c

temp_functions.o: temp_functions.c
	gcc -c -o temp_functions.o temp_functions.c

clean:
	rm -rf *.o main