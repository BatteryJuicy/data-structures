CC = gcc
CFLAGS = -Wall -g

tree: tree.c
	@echo making tree...
	@$(CC) $(CFLAGS) tree.c -o tree

stack: stack.c
	@echo making stack...
	@$(CC) $(CFLAGS) stack.c -o stack

queue: queue.c
	@echo making queue...
	@$(CC) $(CFLAGS) queue.c -o queue

clean:
	rm -f tree
	rm -f stack
	rm -f queue