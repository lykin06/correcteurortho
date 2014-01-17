CC=gcc
CFLAGS=-Wall -std=c99 -g

EXE= test_hash

all: $(EXE)

test_hash: main.o hash.o
	$(CC) $(CFLAGS) -o $@ $^

test_corpus: main.o corpus.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(EXE) *.o *~
