#include <stdio.h>
#include <stdlib.h>

typedef struct list{
    int data;
    struct list *next;
}Node;

Node* create_empty_list();
void insert(Node**, int, int);
void delete(Node*, int);
Node* search(Node*, int);

int main()
{
    Node* head = NULL;

    for (int i = 0; i < 10; i++)
    {
        insert(&head, i, i%2);
    }
    for (Node* pos = head; pos; pos = pos->next)
    {
        printf("%d\n", pos->data);
    }
    
    return 0;
}

void insert(Node** headptr, int i, int data)
{
    Node *new_node = (Node*) malloc(sizeof(Node));
    if (new_node == NULL){
        printf("cannot allocate cell");
        exit(1);
    }
    new_node->data = data;

    int index = 0;
    Node* prevp = NULL;
    Node* p = *headptr;
    while(p && index < i)
    {
        prevp = p;
        p = p->next;
        index++;
    }
    
    if (index == 0)
    {
        new_node->next = *headptr;
        *headptr = new_node;
        return;
    }
    new_node->next = prevp->next;
    prevp->next = new_node;
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