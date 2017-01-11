CPP = g++
CFLAGS = -Wall -g
all:
	$(CPP) $(CFLAGS) -c tmatrix.cpp
	$(CPP) $(CFLAGS) -c smatrix.cpp
	$(CPP) $(CFLAGS) -c run.cpp
	$(CPP) run.o tmatrix.o smatrix.o -o editor -lncurses

clean:
	rm -f a.out editor *.o
