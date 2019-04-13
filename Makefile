shell : shell.o builtin.o
	gcc -o shell shell.o builtin.o

shell.o : shell.h builtin.h shell.c
	gcc -c -o shell.o shell.c

builtin.o : builtin.h builtin.c
	gcc -c -o builtin.o builtin.c

clean:
	rm -f *.o
	rm -f shell
