all:
	gcc -c -Wall tmatrix.c
	gcc -c -Wall smatrix.c
	gcc -c -Wall run.c
	gcc -Wall run.o tmatrix.o smatrix.o -lncurses

clean:
	rm -f a.out *.o
	$(MAKE) clean -C testing/
