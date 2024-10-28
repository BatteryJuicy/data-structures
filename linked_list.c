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
int access(Node*, int);
int list_length(Node*);
void print_list(Node*);

void insert_before_key(Node**, int, int);
void Remove(Node**, int);

int main()
{
    Node* head = NULL;

    for (int i = 0; i < 3; i++)
    {
        insert(&head, i, i+1);
    }

    insert(&head, 2, 99);
    insert(&head, 0, -5);
    insert(&head, 30, 6);

    print_list(head);

    Remove(&head, 0);
    printf("\n");
    print_list(head);

    Remove(&head, 4);

    printf("\n");
    print_list(head);

    Remove(&head, 5);
    printf("\n");
    print_list(head);
    
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
    while(p != NULL && index < i)
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

int access(Node* head, int i){
    int j = 0;
    for (Node* p = head; p; p = p->next)
    {
        if (j == i)
        {
            return p->data;
        }
        j++;
    }
    exit(2);
}

int list_length(Node* head)
{
    int length = 0;
    for (Node* p = head; p; p = p->next)
    {
        length ++;
    }
    return length;
}

void print_list(Node* head)
{
    for (int i = 0; i < list_length(head); i++)
    {
        printf("the %dth element is: %d\n", i+1, access(head, i));
    }
}

void insert_before_key(Node** head, int k1, int k2)
{
    Node *new_node = (Node*) malloc(sizeof(Node));
    if (new_node == NULL){
        printf("cannot allocate cell");
        exit(1);
    }
    new_node->data = k2;

    Node *prevp = NULL;
    Node* p = *head;
    while(p != NULL && p->data != k1)
    {
        prevp = p;
        p = p->next;
    }
    if (p == NULL) exit(2);

    if (prevp == NULL)
    {
        new_node->next = p;
        *head = new_node;
        return;
    }
    new_node->next = p;
    prevp->next = new_node;

}

void Remove(Node** headptr, int index)
{
    if (*headptr == NULL || index < 0) return;

    if (index == 0)
    {
        Node* temp = *headptr;
        *headptr = (*headptr)->next;
        free(temp);
        return;
    }

    Node* prevp = NULL;
    Node* p = (*headptr);
    int i = 1;
    while(p->next != NULL && i < index)
    {
        prevp = p;
        p = p->next;
        i++;
    }
    Node* tmp = p->next;
    if (p->next == NULL)
        prevp->next = p->next;
    else 
        p->next = p->next->next;

    free(tmp);
}