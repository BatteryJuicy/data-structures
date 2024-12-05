#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct tree 
{
    int data;
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

    if(parent->data < k)
        parent->rc = new_node;
    else
        parent->lc = new_node;
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

//----------------hy240 ask2a-------------------

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

int main(int argc, char** argv)
{
    node* root = create_empty_tree(30);

    insert(root, 50);
    insert(root, 40);
    insert(root, 60);
    insert(root, 30);
    insert(root, 10);
    insert(root, 20);
    insert(root, 0);
    insert(root, 13);
    insert(root, 90);
    insert(root, 12);
    insert(root, 9);
    insert(root, 5);

    print_tree(root);

    ask2a(root);

    printf("hh");

    print_tree(root);

}