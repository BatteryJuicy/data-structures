CC=gcc
CFLAGS=-Wall -g

all: clean object_files cs240Elections run

cs240Elections: main.o elections.o
	@echo 5. linking and creating cs240Elections...
	@$(CC) $(CFLAGS) $< -o $@

object_files: main.c elections.c
	@echo 3. making elections.o...
	@$(CC) $(CFLAGS) -c elections.c -o elections.o
	@echo 4. making main.o...
	@$(CC) $(CFLAGS) -c main.c -o main.o

run: cs240Elections
	@echo 6. running cs240Elections
	@./cs240Elections

.PHONY: clean

clean:
	@echo 1. clearing object files
	@rm -f main.o elections.o
	@echo 2. deleting cs240Elections
	@rm -f cs240Elections
