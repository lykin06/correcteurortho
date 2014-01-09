CC=gcc
CFLAGS=-Wall -std=c99 -g

EXE= impl-1

all: $(EXE)

impl-1: main.o hash.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(EXE) *.o *~
