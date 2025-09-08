CC = gcc
CFLAGS = -pedantic -Wall

SRCDIR = src
OUTDIR = out

all: $(OUTDIR) $(OUTDIR)/hashtable

$(OUTDIR):
	@mkdir out

$(OUTDIR)/hashtable: $(SRCDIR)/hashtable.c | $(OUTDIR)
	@echo Making hashtable...
	@$(CC) $(CFLAGS) $^ -o $@

run:
	@echo Running hashtable
	@./$(OUTDIR)/hashtable

clean:
	@rm -f $(OUTDIR)/hashtable.exe

.PHONY: all run clean 