SUBDIRS := $(wildcard */Makefile)
SUBDIRS := $(dir $(SUBDIRS))

.PHONY: all run clean $(SUBDIRS)

# Build everything by default
all: $(SUBDIRS) finish_msg

finish_msg:
	@echo All processes finished.

# Default build rule for subdirs
$(SUBDIRS):
	$(MAKE) -C $@
	
# Run rule → call "make run" inside each subdir
run: $(SUBDIRS:%=run-%)

run-%:
	$(MAKE) -C $* run

# Clean rule → call "make clean" inside each subdir
clean: $(SUBDIRS:%=clean-%)

clean-%:
	$(MAKE) -C $* clean