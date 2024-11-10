CC=gcc
CFLAGS=-Wall -g

all: clean run

cs240Elections: main.c elections.h
	$(CC) $(CFLAGS) $< -o $@

run: cs240Elections
	./cs240Elections.out

.PHONY: clean

clean:
	rm -f cs240Elections
