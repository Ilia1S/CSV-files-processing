all: prog

prog: main.o temp_functions.o
	gcc -std=c99 -o prog main.o temp_functions.o

main.o: main.c temp_functions.h
	gcc -std=c99 -c -o main.o main.c

temp_functions.o: temp_functions.c temp_functions.h
	gcc -std=c99 -c -o temp_functions.o temp_functions.c
	
clean:
	Srm -rf *.o prog
	del *.o
	del prog.exe
