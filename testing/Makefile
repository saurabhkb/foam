test: editor.o simulator.o
	gcc editor.o simulator.o -o simulator -lncurses

editor.o:
	gcc -c ../editor.c

simulator.o:
	gcc -c simulator.c

clean:
	rm -f *.o simulator
