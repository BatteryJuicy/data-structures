#include <stdio.h>
#include <stdlib.h>

#ifndef TREEUTILS_H
#define TREEUTILS_H

/*NOTE: in each file this is included the struct tree must have the following member variables in this order:
    int data;
    struct tree* left_child;
    struct tree* right_child;

It can have more members but these 3 must be the first declared and in this order.
The names of the variables do not matter.

(If left_child and right_child are switched the tree is printed mirrored)
*/
typedef struct tree node;
typedef struct Qnode Qnode;
typedef struct queue queue;

void inorderPrint(node*);
int get_height(node*);
void enqueue(queue*,node*);
node* dequeue(queue*);
int isEmptyQueue(queue*);
void print_tree(node*, int);

#endif
