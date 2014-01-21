CC=gcc
CFLAGS=-Wall -std=c99 -g

EXE= test1 test2 correcteur

all: $(EXE)

test1: test1.o hash.o
	$(CC) $(CFLAGS) -o test1 test1.o hash.o

test2: test2.o hash.o corpus.o
	$(CC) $(CFLAGS) -o test2 test2.o hash.o corpus.o

correcteur: main.o hash.o corpus.o correct.o
	$(CC) $(CFLAGS) -o correcteur main.o hash.o corpus.o correct.o

clean:
	rm -f $(EXE) *.o *~

main.o: main.c corpus.h hash.h correct.h

test1.o: test1.c hash.h

test2.o: test2.c hash.h corpus.h

hash.o: hash.c hash.h

corpus.o: corpus.c corpus.h

correct.o: correct.h correct.h

