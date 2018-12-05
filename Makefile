CC = g++

CFLAGS=-O2 -fomit-frame-pointer -march=native -std=c++11

all :
	$(CC) $(CFLAGS) -c main.cpp Scheme.cpp
	$(CC) $(CFLAGS) -o test main.o Scheme.o
	

clean :
	rm -f *.o


new :
	make all
	make clean
	./test