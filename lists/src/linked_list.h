#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct list{
    int data;
    struct list *next;
}Node;

//insert node before a given INDEX.
void insert(Node**, int, int);
//delete node with a certain VALUE.
void delete(Node**, int);
//return POINTER to a node with a certain VALUE.
Node* search(Node*, int);
//return the VALUE of the node at some INDEX.
int access(Node*, int);
//returns the number of nodes.
int list_length(Node*);
//prints the contents of the list.
void print_list(Node*);

//----hy240 functions----
//inserts node with a given value before the node with the sought after value.
void insert_before_key(Node**, int, int);
//deletes a node at a ceratin INDEX.
void Remove(Node**, int);
#endif