#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct tree 
{
    int data;
    struct tree* lc;
    struct tree* rc;
    int height;
}node;

int get_height(node* root)
{
    if (root == NULL)
        return -1;

    int leftHeight = get_height(root->lc);
    int rightHeight = get_height(root->rc);
    root->height = leftHeight > rightHeight ? leftHeight : rightHeight;
    return root->height + 1;
}

void insert(node* root, int k) //sorted BST
{
    node* parent = NULL;
    node* q = root;

    while(q != NULL)
    {
        if (k == q->data){
            printf("node with data %d already exists\n", k);
            return;
        }
        parent = q;
        if (q->data < k)
            q = q->rc;
        else
            q = q->lc;
    }
    if (parent == NULL){
        printf("empty tree");
        exit(1);
    }

    node *new_node = (node*) malloc(sizeof(node));
    if (new_node == NULL){
        printf("couldn't allocate node with data %d exiting...", k);
        exit(1);
    }
    new_node->lc = new_node->rc = NULL;
    new_node->data = k;
    new_node->height = 0;

    if(parent->data < k)
        parent->rc = new_node;
    else
        parent->lc = new_node;
    get_height(root);
}

node* create_empty_tree(int k)
{
    node *root = (node*) malloc(sizeof(node));
    if (root == NULL){
        printf("couldn't allocate empty tree exiting...");
        exit(1);
    }
    root->data = k;
    root->lc = root->rc = NULL;
    return root;
}

#include "printTree.h"

int main(int argc, char** argv)
{
    node* root = create_empty_tree(5);

    insert(root, 5);
    insert(root, 4);
    insert(root, 6);
    insert(root, 3);
    insert(root, 1);
    insert(root, 2);
    insert(root, 0);
    insert(root, 7);
    insert(root, 9);
    insert(root, 8);

    print_tree(root);
}