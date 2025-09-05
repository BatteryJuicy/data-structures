#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct tree 
{
    int data;
    int height;
    struct tree* parent;
    struct tree* lc;
    struct tree* rc;
}node;

#include "printTree.h"

void fix_height(node* node_)
{
    if (node_ == NULL) return;

    int lh = node_->lc ? node_->lc->height : -1;
    int rh = node_->rc ? node_->rc->height : -1;
    node_->height = (lh > rh ? lh : rh) + 1; // max(lh, rh) + 1.
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
    new_node->height = 0;

    return new_node;
}

int calculate_balance(node* node_)
{
    if (node_ == NULL) return 0;

    int left_height = node_->lc ? node_->lc->height : -1;
    int right_height = node_->rc ? node_->rc->height : -1;

    int balance = right_height - left_height;
    return balance;
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

    //fix heights
    fix_height(x);
    fix_height(y);

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

    //fix heights
    fix_height(y);
    fix_height(x);

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
        fix_height(node_);

        int balance = calculate_balance(node_);

        //if node is left heavy.
        if (balance < -1){//critical node
            //if left child is right heavy.
            if (node_->lc != NULL && calculate_balance(node_->lc) > 0){ //true: LR. false: LL.
                node_->lc = left_rotate(node_->lc);
            }
            node_ = right_rotate(node_); //only or second rotation depending on which case it is (LR or LL).
        }
        //if node is right heavy.
        else if (balance > 1){//crtitical node
            //if right child is left heavy/
            if (node_->rc != NULL && calculate_balance(node_->rc) < 0){ //true: RL, false: RR
                node_->rc = right_rotate(node_->rc);
            }
            node_ = left_rotate(node_); //only or second rotation depending on which case it is (RL or RR).
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
    *root = balance_tree(new_node); //the only case where the root value will change is if function performs a rotation on the root.

    print_tree(*root);
    printf("\n--------------------------------------------\n");
}

void inorder(node* root) {
    if (!root) return;
    inorder(root->lc);
    printf("%d ", root->data);
    inorder(root->rc);
}

int main()
{
    node* root = NULL;

    insert(&root, 1);
    insert(&root, 2);
    insert(&root, 6);
    insert(&root, 10);
    insert(&root, 4);
    insert(&root, 5);
    insert(&root, 3);
    insert(&root, 7);
    insert(&root, 9);
    insert(&root, 8);

    printf("height: %d\n", root->height);
    printf("spaces: %d\n", (1 << 3)/(3+1) - 1);

    print_tree(root);
    inorder(root);
}