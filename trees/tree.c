#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct tree 
{
    int data;
    struct tree* lc;
    struct tree* rc;
}node;

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

void print_level(node* root, int level)
{
    if (root == NULL){
        print_node(NULL);
        return;
    }
    if (level == 1){
        print_node(root);
    }
    else if (level > 1)
    {
        print_level(root->lc, level - 1);
        printf(" ");
        print_level(root->rc, level - 1);
    }
}
//todo: make it look better
void print_tree(node* root)
{
    int height = get_height(root);
    for (int i = 1; i <= height; i++)
    {
        for (int j = (pow(2, height-1)) - i-1; j > 0  ; j--)
        {
            putchar(' ');
        }
        
        print_level(root, i);
        printf("\n");
    }
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

    insertRC(root, 5);
    insertLC(root, 4);
    insertRC(root->rc, 6);
    insertRC(root->lc, 3);
    insertLC(root->rc, 1);
    insertLC(root->lc, 2);

    print_tree(root);

}