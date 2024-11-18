CC=gcc
CFLAGS= -Wall -g

all: cleanAll object_files cs240Elections clean

cs240Elections: main.o elections.o
	@echo 5. linking and creating cs240Elections...
	@$(CC) $(CFLAGS) main.o elections.o -o cs240Elections
	@echo DONE

object_files: main.c elections.c
	@echo 3. making elections.o...
	@$(CC) $(CFLAGS) -c elections.c -o elections.o
	@echo 4. making main.o...
	@$(CC) $(CFLAGS) -c main.c -o main.o
	@echo COMPILED

run1: cs240Elections
	@echo A. running cs240Elections with input small...
	@./cs240Elections ../testfiles/small
	@echo 6. clearing object files...
	@rm -f main.o elections.o

run2: cs240Elections
	@echo B. running cs240Elections with input medium...
	@./cs240Elections ../testfiles/medium
	@echo 6. clearing object files...
	@rm -f main.o elections.o

run3: cs240Elections
	@echo C. running cs240Elections with input large...
	@./cs240Elections ../testfiles/large
	@echo 6. clearing object files...
	@rm -f main.o elections.o

.PHONY: clean

cleanAll:
	@echo 1. clearing object files...
	@rm -f main.o elections.o
	@echo 2. deleting cs240Elections...
	@rm -f cs240Elections

clean:
	@echo 6. clearing object files...
	@rm -f main.o elections.o
