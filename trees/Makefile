CC = gcc
CFLAGS = -Wall

SRCDIR = src
OUTDIR = out

all: $(OUTDIR) treeUtils tree bst avl redblack
treeUtils: $(OUTDIR)/treeUtils.o
tree: $(OUTDIR)/tree
bst: $(OUTDIR)/bst
avl: $(OUTDIR)/avl
redblack: $(OUTDIR)/redblack

$(OUTDIR):
	@mkdir out

#---------------COMPILE TARGETS---------------

#object file
$(OUTDIR)/treeUtils.o: $(SRCDIR)/treeUtils.c $(SRCDIR)/treeUtils.h
	@$(CC) $(CFLAGS) -c $< -o $@

$(OUTDIR)/tree: $(SRCDIR)/tree.c $(OUTDIR)/treeUtils.o | $(OUTDIR)
	@echo Making binary tree...
	@$(CC) $(CFLAGS) $^ -o $@

$(OUTDIR)/bst: $(SRCDIR)/BST.c $(OUTDIR)/treeUtils.o | $(OUTDIR)
	@echo Making bst...
	@$(CC) $(CFLAGS) $^ -o $@

$(OUTDIR)/avl: $(SRCDIR)/AVL.c $(OUTDIR)/treeUtils.o | $(OUTDIR)
	@echo Making avl...
	@$(CC) $(CFLAGS) $^ -o $@

$(OUTDIR)/redblack: $(SRCDIR)/redblack.c $(OUTDIR)/treeUtils.o | $(OUTDIR)
	@echo Making redblack
	@$(CC) $(CFLAGS) $^ -o $@

#---------------RUN TARGETS---------------

runTree: $(OUTDIR) $(OUTDIR)/treeUtils.o $(OUTDIR)/tree
	@echo Running: tree
	@./$(OUTDIR)/tree

runBST: $(OUTDIR) $(OUTDIR)/treeUtils.o $(OUTDIR)/bst
	@echo Running: bst
	@./$(OUTDIR)/bst

runAVL: $(OUTDIR) $(OUTDIR)/treeUtils.o $(OUTDIR)/avl
	@echo Running: avl
	@./$(OUTDIR)/avl

runRB: $(OUTDIR) $(OUTDIR)/treeUtils.o $(OUTDIR)/redblack
	@echo Running redblack
	@./$(OUTDIR)/redblack

run: runTree runBST runAVL runRB

clean:
	@rm -f $(OUTDIR)/tree
	@rm -f $(OUTDIR)/bst
	@rm -f $(OUTDIR)/avl

.PHONY: all treeUtils tree bst avl redblack run runTree runBST runAVL runRB clean