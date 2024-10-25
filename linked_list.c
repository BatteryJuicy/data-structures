#include <stdio.h>
#include <stdlib.h>

typedef struct list{
    int data;
    struct list *next;
}Node;

Node* create_empty_list();
void addAt(Node*, int);
void delete(Node*, int);
Node* search(Node*, int);

int main(int argc, char **argv)
{
    Node* head = create_empty_list();

    for (int i = 0; i < 10; i++)
    {
        addAt(head, i);
    }
    for (Node* pos = 0; pos; pos++)
    {
        printf("%d\n", pos->data);
    }
    
    return 0;
}

Node* create_empty_list()
{
    Node *head = (Node*) malloc(sizeof(Node));
    if( head == NULL){
        printf("cannot allocate node.");
        exit(1);
    }
    head->next = NULL;
    return head;
}

void addAt(Node* pos, int data)
{
    Node *new_node = (Node*) malloc(sizeof(Node));
    if (new_node == NULL){
        printf("cannot allocate cell");
        exit(1);
    }
    new_node->next = pos->next;
    pos->next = new_node;
    new_node->data = data;
}

void delete(Node* head, int x)
{
    Node* prev = NULL;
    Node* index = head;

    while(index != NULL && index->data != x)
    {
        prev = index;
        index = index->next;
    }

    if (index == NULL) exit(2);
    prev->next = index->next;

    free(index);
    free(prev);
}

Node* search(Node* head, int x)
{
    while(head != NULL && head->data != x)
    {
        head = head->next;
    }
    if (head == NULL) return NULL;
    return head;
}