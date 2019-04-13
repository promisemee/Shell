shell : shell.o
	gcc -o shell shell.o

shell.o : shell.h shell.c
	gcc -c -o shell.o shell.c


clean:
	rm -f *.o
	rm -f shell
