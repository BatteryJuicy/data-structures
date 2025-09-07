#include "treeUtils.h"

struct tree{
    int data;
    struct tree* lc;
    struct tree* rc;
};

void inorderPrint(node* root) {
    static int callStackCount = 0;
    callStackCount++;
    if (!root) {
        callStackCount--;
        return;
    }
    inorderPrint(root->lc);
    printf("%d ", root->data);
    inorderPrint(root->rc);
    if(callStackCount <= 0)
        printf("\n");
}

int get_height(node* root)
{
    if (root == NULL)
        return -1;

    int leftHeight = get_height(root->lc);
    int rightHeight = get_height(root->rc);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

struct Qnode {
    node* treeNode;
    struct Qnode* next;
};

struct queue {
    Qnode* front;
    Qnode* rear;
};

void enqueue(queue* q, node* tn) {
    Qnode* new_node = (Qnode*) malloc(sizeof(Qnode));
    new_node->treeNode = tn;
    new_node->next = NULL;
    if (!q->rear) {
        q->front = q->rear = new_node;
        return;
    }
    q->rear->next = new_node;
    q->rear = new_node;
}

node* dequeue(queue* q) {
    if (!q->front) return NULL; // empty
    Qnode* temp = q->front;
    node* val = temp->treeNode;
    q->front = q->front->next;
    if (!q->front) q->rear = NULL;
    free(temp);
    return val;
}

int isEmptyQueue(queue* q){
    if(q->front == NULL) return 1;
    return 0;
}

void print_tree(node* root, int tree_height){
    if (!root) return;

    queue Q = {NULL, NULL};
    enqueue(&Q, root);

    int level = 0;

    while (!isEmptyQueue(&Q) && level <= tree_height) {
        int nodes_in_level = 1 << level; //2^level.
        for (int i = 0; i < nodes_in_level && !isEmptyQueue(&Q); i++) {
            node* P = dequeue(&Q);

            int spaces = (1 << (tree_height - level+1)) - 1;
            for (int s = 0; s < spaces; s++) putchar(' ');

            if (P) {
                printf("%d", P->data);
                enqueue(&Q, P->lc);
                enqueue(&Q, P->rc);
            } else {
                printf("_");
            }

            for (int s = 0; s <= spaces; s++) putchar(' ');
        }
        printf("\n");
        level++;
    }
}
