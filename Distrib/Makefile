CC=gcc
CFLAGS=-Wall -std=c99 -g

EXE= impl-1 #impl-2

all: $(EXE)

impl-1: main.o hash.o
	$(CC) $(CFLAGS) -o $@ $^

#impl-2: main.o table-liste.o
#	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(EXE) *.o *~
