#include <stdio.h>
#include <stdlib.h>

typedef struct list{
    int data;
    struct list *next;
}Node;

//insert node before a given INDEX.
void insert(Node**, int, int);
//delete node with a certain VALUE.
void delete(Node**, int);
//return POINTER to a node with a certain VALUE.
Node* search(Node*, int);
//return the VALUE of the node at some INDEX.
int access(Node*, int);
//returns the number of nodes.
int list_length(Node*);
//prints the contents of the list.
void print_list(Node*);

//----hy240 functions----
//inserts node with a given value before the node with the sought after value.
void insert_before_key(Node**, int, int);
//deletes a node at a ceratin INDEX.
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
    //creating new node and making sure it got allocated.
    Node *new_node = (Node*) malloc(sizeof(Node));
    if (new_node == NULL){
        printf("cannot allocate cell");
        exit(1);
    }
    new_node->data = data;

    //iterating the linked list until the node at index i is found.
    int index = 0;
    Node* prevp = NULL;
    Node* p = *headptr;
    while(p != NULL && index < i)
    {
        prevp = p;
        p = p->next;
        index++;
    }
    
    //if list is empty or we need to add a node at the start of the list.
    if (index == 0)
    {
        new_node->next = *headptr;
        *headptr = new_node;
        return;
    }

    //otherwise if the node is in the middle or at the end.
    new_node->next = prevp->next;
    prevp->next = new_node;
}

void delete(Node** head, int x)
{
    Node* prevp = NULL;
    Node* p = *head;

    while(p != NULL && p->data != x)
    {
        prevp = p;
        p = p->next;
    }

    if (p == NULL) 
    exit(2);

    if (prevp == NULL)
    {
        *head =  p->next;
        free(p);
        return;
    }
    
    //otherwise if the node to be deleted is not first.
    prevp->next = p->next;

    free(p);
    free(prevp);
}

Node* search(Node* head, int x)
{
    while(head != NULL && head->data != x)
    {
        head = head->next;
    }
    if (head == NULL) 
        return NULL;

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
        printf("element at index %d: %d\n", i, access(head, i));
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