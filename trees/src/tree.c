#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct tree 
{
    int data;
    int height;
    struct tree* lc;
    struct tree* rc;
}node;

int get_height(node* root)
{
    if (root == NULL)
        return 0;

    int leftHeight = get_height(root->lc);
    int rightHeight = get_height(root->rc);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

void insertLC(node* parent, int data)
{
    node* new_child = (node*) malloc(sizeof(node));
    new_child->data = data;
    new_child->lc = NULL;
    new_child->rc = NULL;
    new_child->height = 0;

    parent->lc = new_child;
    parent->height = get_height(parent);
}
void insertRC(node* parent, int data)
{
    node* new_child = (node*) malloc(sizeof(node));
    new_child->data = data;
    new_child->lc = NULL;
    new_child->rc = NULL;
    new_child->height = 0;

    parent->rc = new_child;
    parent->height = get_height(parent);
}

int isLeaf(node* node_)
{
    if (node_->lc == NULL && node_->rc == NULL)
        return 1;
    return 0;
}

#include "printTree.h"

node* create_empty_tree(int k)
{
    node *new_node = (node*) malloc(sizeof(node));
    if (new_node == NULL){
        printf("couldn't allocate empty tree exiting...");
        exit(1);
    }
    new_node->data = k;
    new_node->height = 0;
    new_node->lc = new_node->rc = NULL;
    return new_node;
}

int main()
{
    node* root = create_empty_tree(3);

    insertRC(root, 5);
    insertLC(root, 4);
    insertRC(root->rc, 6);
    insertRC(root->lc, 3);
    insertLC(root->rc, 1);
    insertLC(root->lc, 2);

    print_tree(root);

}