#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct tree 
{
    int data;
    int depth;
    int balance; // values should be: -1, 0, 1. Otherwise the tree needs to be rebalanced.
    struct tree* parent;
    struct tree* lc;
    struct tree* rc;
}node;

void print_node(node* node_)
{
    if ( node_ == NULL){
        printf("_");
        return;
    }

    printf("%d", node_->data);
}

int isLeaf(node* node_)
{
    if (node_->lc == NULL && node_->rc == NULL)
        return 1;
    return 0;
}

int get_height(node* root)
{
    if (root == NULL)
        return 0;

    int leftHeight = get_height(root->lc);
    int rightHeight = get_height(root->rc);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

void print_level(node* node, int level)
{
    if (node == NULL){
        print_node(NULL);
        return;
    }
    if (level == 1){
        print_node(node);
    }
    else if (level > 1)
    {
        print_level(node->lc, level - 1);
        putchar(' ');
        print_level(node->rc, level - 1);
    }
}

void print_tree(node* root)
{
    int height = get_height(root);
    for (int i = 1; i <= height; i++)
    {
        for (int j = 0; j < 3*height - 2*i ; j++)
        {
            putchar(' ');
        }
        
        print_level(root, i);
        printf("\n");
    }
}

node* create_node(int data, int depth)
{
    node *new_node = (node*) malloc(sizeof(node));
    if (new_node == NULL){
        printf("couldn't allocate node with\n\tdata: %d\n\tdepth: %d\n", data, depth);
        exit(1);
    }
    new_node->lc = new_node->rc = new_node->parent = NULL;
    new_node->data = data;
    new_node->depth = depth;
    new_node->balance = 0;

    return new_node;
}

void calculate_balance(node* node)
{
    int left_height;
    int right_height;

    left_height = get_height(node->lc);
    right_height = get_height(node->rc);

    int balance = right_height - left_height;
    node->balance = balance;
}

void insert(node** root, int k)
{
    node* parent = NULL;
    node* q = *root;

    int depth = 0;

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
        depth++;
    }

    node* new_node = create_node(k, depth);
    calculate_balance(new_node);

    //if the node is not the root.
    if (parent != NULL)
    {
        if(parent->data < k)
            parent->rc = new_node;
        else
            parent->lc = new_node;
    }
    else{   //if the tree is empty.
        *root = new_node;
    }
    new_node->parent = parent;

    //balance the tree if needed.
    q = new_node;
    for (int i = depth; i > 0; i--)
    {
        if(q->balance < -1 || q->balance > 1){
            balance_tree();
        }
        q = q->parent;
    }
    
}

int main(int argc, char** argv)
{
    node* root = NULL;

    insert(&root, 30);

    print_tree(root);
}