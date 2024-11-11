#compiler flags
CFLAGS = -Wall -g

#target name
NAME = linked_list

#source and output directories
SRC_DIR = src
OBJ_DIR = build

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)

	@echo "Compiling $< into $@..."
	gcc $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	mkdir -p out
	@echo "Linking $(NAME)..."

	gcc $(CFLAGS) $(OBJECTS) -o out/$(NAME)

#--------------------------------------------------
dlist: doubly_linked_list.c
	@gcc -Wall -g doubly_linked_list.c -o dlist

run1:
	@echo linked list:
	@./out/linked_list

run2:
	@echo doubly linked list:
	@./dlist

clean:
	rm -f linked_list
	rm -f dlist
	rm -f $(OBJ_DIR)/linked_list.o
	rm -f $(OBJ_DIR)/linked_list_main.o