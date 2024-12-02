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

int main()
{
    node* root = create_empty_tree(3);

    insert(root, 5);
    insert(root, 4);
    insert(root, 6);
    insert(root, 3);
    insert(root, 1);
    insert(root, 2);
    insert(root, 0);
    insert(root, 10);
    insert(root, 9);
    insert(root, 12);
    insert(root, -1);
    insert(root, -5);

    print_tree(root);

}