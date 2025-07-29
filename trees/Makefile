CC = gcc
CFLAGS = -Wall

SRCDIR = src
OUTDIR = out

all: $(OUTDIR)/tree $(OUTDIR)/bst $(OUTDIR)/avl

.PHONY: all tree bst avl

tree: $(OUTDIR)/tree
bst:  $(OUTDIR)/bst
avl:  $(OUTDIR)/avl

$(OUTDIR):
	@mkdir -p out


$(OUTDIR)/tree: $(SRCDIR)/tree.c | $(OUTDIR)
	@echo making tree...
	@$(CC) $(CFLAGS) -lm $< -o $(OUTDIR)/tree

$(OUTDIR)/bst: $(SRCDIR)/BST.c | $(OUTDIR)
	@echo making bst...
	@$(CC) $(CFLAGS) $< -o $(OUTDIR)/bst

$(OUTDIR)/avl: $(SRCDIR)/AVL.c | $(OUTDIR)
	@echo making avl...
	@$(CC) $(CFLAGS) $< -o $(OUTDIR)/avl

clean:
	@rm -f $(OUTDIR)/tree
	@rm -f $(OUTDIR)/bst
	@rm -f $(OUTDIR)/avl