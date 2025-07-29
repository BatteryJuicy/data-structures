#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct tree 
{
    int data;
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

int get_height(node* root)
{
    if (root == NULL)
        return 0;

    int leftHeight = get_height(root->lc);
    int rightHeight = get_height(root->rc);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

void print_level(node* node_, int level)
{
    if (node_ == NULL){
        print_node(NULL);
        return;
    }
    if (level == 1){
        print_node(node_);
    }
    else if (level > 1)
    {
        print_level(node_->lc, level - 1);
        putchar(' ');
        print_level(node_->rc, level - 1);
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

node* create_node(int data)
{
    node *new_node = (node*) malloc(sizeof(node));
    if (new_node == NULL){
        printf("couldn't allocate node with\n\tdata: %d\n", data);
        exit(1);
    }
    new_node->lc = new_node->rc = new_node->parent = NULL;
    new_node->data = data;
    new_node->balance = 0;

    return new_node;
}

void calculate_balance(node* node_)
{
    int left_height;
    int right_height;

    left_height = get_height(node_->lc);
    right_height = get_height(node_->rc);

    int balance = left_height - right_height;
    node_->balance = balance;
}

node* left_rotate(node* x)
{
    node* y = x->rc; 
    node* b = y->lc;
    /*
              x
            /   \ 
           a     y
                / \ 
               b   c
    */

    //rotate.
    y->lc = x;
    x->rc = b;

    if (b != NULL)
        b->parent = x;

    y->parent = x->parent;
    x->parent = y;

    calculate_balance(x);
    calculate_balance(y);

    if (y->parent == NULL)
        return y;

    if (y->parent->rc == x){
        y->parent->rc = y;
    }
    else if (y->parent->lc == x){
        y->parent->lc = y;
    }

    return y;
}

node* right_rotate(node* y)
{
    node* x = y->lc;
    node* b = x->rc;
    /*
              y
            /   \ 
           x     c
          / \ 
         a   b
    */

    //rotate.
    x->rc = y;
    y->lc = b;

    if (b != NULL)
        b->parent = y;

    x->parent = y->parent;
    y->parent = x;

    calculate_balance(x);
    calculate_balance(y);

    if (x->parent == NULL)
        return x;

    if (x->parent->rc == y){
        x->parent->rc = x;
    }
    else if (x->parent->lc == y){
        x->parent->lc = x;
    }

    return x;
}

node* balance_tree(node* node_)
{   

    while(node_ != NULL)
    {
        calculate_balance(node_);

        if (node_->balance >= 2){
            if (node_->lc != NULL && node_->lc->balance < 0){
                node_->lc = left_rotate(node_->lc);
            }
            node_ = right_rotate(node_);
        }
        else if (node_->balance <= -2){
            if (node_->rc != NULL && node_->rc->balance > 0){
                node_->rc = right_rotate(node_->rc);
            }
            node_ = left_rotate(node_);
        }

        if (node_->parent == NULL){
            return node_; //return new root.
        }

        node_ = node_->parent;
    }
    return NULL;
}

void insert(node** root, int k)
{
    node* parent = NULL;
    node* q = *root;

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

    node* new_node = create_node(k);

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

    //balance the tree.
    (*root) = balance_tree(new_node); //the only case where the root value will change is if function performs a rotation on the root.

    print_tree(*root);
    printf("\n----------\n");
}

int main()
{
    node* root = NULL;

    insert(&root, 1);
    insert(&root, 2);
    insert(&root, 3);
    insert(&root, 10);
    insert(&root, 5);
    insert(&root, 7);
    insert(&root, 8);

}