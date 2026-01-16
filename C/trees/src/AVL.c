#include <stdio.h>
#include <stdlib.h>

#include "treeUtils.h"

struct tree{
    int key;
    struct tree* lc;
    struct tree* rc;
    struct tree* parent;
    int height;
};

void fix_height(node* node_)
{
    if (node_ == NULL) return;

    int lh = node_->lc ? node_->lc->height : -1;
    int rh = node_->rc ? node_->rc->height : -1;
    node_->height = (lh > rh ? lh : rh) + 1; // max(lh, rh) + 1.
}

node* create_node(int key)
{
    node *new_node = (node*) malloc(sizeof(node));
    if (new_node == NULL){
        printf("couldn't allocate node with\n\tkey: %d\n", key);
        exit(1);
    }
    new_node->lc = new_node->rc = new_node->parent = NULL;
    new_node->key = key;
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
        if (k == q->key){
            printf("node with key %d already exists\n", k);
            return;
        }
        parent = q;
        if (q->key < k)
            q = q->rc;
        else
            q = q->lc;
    }

    node* new_node = create_node(k);

    //if the node is not the root.
    if (parent != NULL)
    {
        if(parent->key < k)
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

    print_tree(*root, get_height(*root));
    printf("\n--------------------------------------------\n");
}

//helper to replace the link between q and q->parent with child and q->parent.
void replace_in_parent(node* q, node* child) {
    if (q->parent) {
        if (q->parent->lc == q)
            q->parent->lc = child;
        else
            q->parent->rc = child;
    }
    if (child)
        child->parent = q->parent;
}

// Find the minimum node starting from a given root.
node* find_min(node* root) {
    while (root && root->lc)
        root = root->lc;
    return root;
}

void delete(node** root, int key)
{
    node* parent = NULL;
    node* q = *root;

    while(q != NULL)
    {
        if (key == q->key){
            if(q->lc == NULL && q->rc == NULL){                     // 0 children
                replace_in_parent(q, NULL); // remove q.
                free(q);
            }
            else if (q->lc != NULL && q->rc != NULL){               // 2 children
                /*since this case has 2 children,
                inOrder successor is guaranted to be in q->rc.*/
                node* successor = find_min(q->rc);
                q->key = successor->key;
                delete(&(q->rc), successor->key);
            }
            else{                                                   // 1 child
                node* child = (q->lc) ? q->lc : q->rc;
                replace_in_parent(q, child);
                free(q);
            }
            *root = balance_tree(parent);
            return;
        }
        parent = q;
        if (q->key < key)
            q = q->rc;
        else
            q = q->lc;
    }
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

    print_tree(root, get_height(root));
    inorderPrint(root);
}