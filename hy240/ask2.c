#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct tree 
{
    int data;
    struct tree* lc;
    struct tree* rc;
}node;

const int MAX = 11;

node* R[20];

void insert_delete_tree(node* new_tree, node* node)
{
    if (node == NULL)
        return;
    
    struct tree *left_temp = node->lc;
    struct tree *right_temp = node->rc;
    
    insert(new_tree, node->data);
    free(node);

    printf("inserting left tree:\n");
    print_tree(new_tree);

    insert_delete_tree(new_tree, left_temp);
    insert_delete_tree(new_tree, right_temp);
}

node* find_successor(node* root)
{
    while(root != NULL && root->lc != NULL)
    {
        root = root->lc;
    }
    return root;
}

node* find_successor_parent(node* root)
{
    while(root != NULL && root->lc != NULL && root->lc->lc != NULL)
    {
        root = root->lc;
    }
    return root;
}

void delete(node* parent, node* child)
{
    node** parent_child_ptr;
    if (parent->lc == child)
        parent_child_ptr = &(parent->lc);
    else
        parent_child_ptr = &(parent->rc);

    if (child->lc == NULL && child->rc == NULL)
    {
        *parent_child_ptr = NULL;

        free(child);
    }
    else if (child->rc == NULL)
    {
        *parent_child_ptr = child->lc;
        free(child);
    }
    else if (child->lc == NULL)
    {
        *parent_child_ptr = child->rc;
        free(child);
    }
    else
    {
        node* suc_parent = find_successor_parent((child->rc));
        node* successor = find_successor(child->rc);

        child->data = successor->data;
        
        delete(suc_parent, successor);
    }
}

void insert_delete_no_left(node* new_tree, node* parent, node* root)
{
    insert(new_tree, root->data);
    delete(parent, root);

    printf("inserting node %d\n", root->data);
    print_tree(new_tree);
    
}

void insert_delete(node* new_tree, node* parent, node* node, int lower, int higher)
{
    if (node == NULL)
        return;
    
    insert_delete_tree(new_tree, node->lc);
    node->lc = NULL;

    while(node != NULL && node->data < higher)
    {
        insert_delete_no_left(new_tree, parent, node);
    }
}

void ask2a(node* root)
{
    int m = 0;
    
    int lower = -MAX;
    int higher = -1;

    node* prev = NULL;
    node*p = root;

    while(p != NULL)
    {
        lower += MAX;
        higher += MAX;

        if (p->data > higher){
            prev = p;
            p = p->lc;
        }
        else{
            print_tree(p);
            R[m] = create_empty_tree(p->data);
            insert_delete(R[m], prev, p, lower, higher);
            m++;
            p = root;
            print_tree(p);
        }
    }
}