#compiler flags
CFLAGS = -Wall -g

#target name
NAME = linked_list

#source and output directories
SRC_DIR = src
OUT_DIR = out

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SRC:$(SRC_DIR)/%.c=$(OUT_DIR)/%.o)

all: $(OUT_DIR) $(OUT_DIR)/$(NAME) $(OUT_DIR)/dlist

$(OUT_DIR): 
	@mkdir $(OUT_DIR)

$(OUT_DIR)/%.o: $(SRC_DIR)/%.c | $(OUT_DIR)
	@echo Compiling $< into $@...
	@gcc $(CFLAGS) -c $< -o $@

$(OUT_DIR)/$(NAME): $(OBJECTS) | $(OUT_DIR)
	@echo Linking $(NAME)...
	@gcc $(CFLAGS) $(OBJECTS) -o $(OUT_DIR)/$(NAME)

#--------------------------------------------------
$(OUT_DIR)/dlist: doubly_linked_list.c
	@echo Making dlist...
	@gcc -Wall -g doubly_linked_list.c -o $(OUT_DIR)/dlist

#==================================================
run1:
	@echo Running linked list:
	@./$(OUT_DIR)/linked_list

run2:
	@echo dlist:
	@./$(OUT_DIR)/dlist

run: run1 run2

clean:
	rm -f $(OUT_DIR)/linked_list
	rm -f $(OUT_DIR)/dlist
	rm -f $(OUT_DIR)/linked_list.o
	rm -f $(OUT_DIR)/linked_list_main.o

.PHONY: all run1 run2 run clean