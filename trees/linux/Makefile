CC = gcc
CFLAGS = -Wall -g

tree: ../tree.c
	@echo making tree...
	@$(CC) $(CFLAGS) ../tree.c -lm -o ./out/tree

bst: ../BST.c
	@echo making bst...
	@$(CC) $(CFLAGS) ../BST.c -o ./out/bst

avl: ../AVL.c
	@echo making avl...
	@$(CC) $(CFLAGS) ../AVL.c -o ./out/avl

clean:
	rm -f tree
	rm -f bst
	rm -f avl