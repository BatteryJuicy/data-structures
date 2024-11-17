CC=gcc
CFLAGS=-g

all: clean object_files cs240Elections

cs240Elections: main.o elections.o
	@echo 5. linking and creating cs240Elections...
	@$(CC) $(CFLAGS) main.o elections.o -o cs240Elections
	@echo DONE

object_files: main.c elections.c
	@echo 3. making elections.o...
	@$(CC) $(CFLAGS) -c elections.c -o elections.o
	@echo 4. making main.o...
	@$(CC) $(CFLAGS) -c main.c -o main.o

run1: cs240Elections
	@echo 61. running cs240Elections
	@./cs240Elections ../testfiles/small
run2: cs240Elections
	@echo 61. running cs240Elections
	@./cs240Elections ../testfiles/medium
run3: cs240Elections
	@echo 61. running cs240Elections
	@./cs240Elections ../testfiles/large

.PHONY: clean

clean:
	@echo 1. clearing object files
	@rm -f main.o elections.o
	@echo 2. deleting cs240Elections
	@rm -f cs240Elections
