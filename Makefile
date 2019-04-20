all : shell

shell : shell.o builtin.o execute.o
	gcc -o shell shell.o builtin.o execute.o

shell.o : execute.h shell.h builtin.h shell.c
	gcc -c -o shell.o shell.c

builtin.o : shell.h builtin.h builtin.c
	gcc -c -o builtin.o builtin.c

execute.o : shell.h execute.h builtin.h execute.c
	gcc -c -o execute.o execute.c

clean:
	rm -f *.o shell
	rm -f test.* test
