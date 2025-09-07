#include <stdio.h>
#include <stdlib.h>

#include "treeUtils.h"

struct tree 
{
    int data;
    struct tree* lc;
    struct tree* rc;
};

void insertLC(node* parent, int data)
{
    node* new_child = (node*) malloc(sizeof(node));
    new_child->data = data;
    new_child->lc = NULL;
    new_child->rc = NULL;

    parent->lc = new_child;
}
void insertRC(node* parent, int data)
{
    node* new_child = (node*) malloc(sizeof(node));
    new_child->data = data;
    new_child->lc = NULL;
    new_child->rc = NULL;

    parent->rc = new_child;
}

int isLeaf(node* node_)
{
    if (node_->lc == NULL && node_->rc == NULL)
        return 1;
    return 0;
}

node* create_empty_tree(int k)
{
    node *new_node = (node*) malloc(sizeof(node));
    if (new_node == NULL){
        printf("couldn't allocate empty tree exiting...");
        exit(1);
    }
    new_node->data = k;
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

    print_tree(root, get_height(root));

}