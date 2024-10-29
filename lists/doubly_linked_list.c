#include <stdio.h>
#include <stdlib.h>

typedef struct list{
    int data;
    struct list *next;
    struct list *prev;
}Node;

void insert_before(Node*, int, int);
void insert_after(Node*, int, int);

int list_length(Node* head)
{
    int length = 0;
    for (Node* p = head->next; p!= head; p = p->next)
    {
        length ++;
    }
    return length;
}
int access(Node* head, int i){
    int j = 0;
    for (Node* p = head->next; p!= head; p = p->next)
    {
        if (j == i)
        {
            return p->data;
        }
        j++;
    }
    exit(2);
}
void print_list(Node* head)
{
    for (int i = 0; i < list_length(head); i++)
    {
        printf("the %dth element is: %d\n", i+1, access(head, i));
    }
}

int main()
{
    Node header = {0, &header, &header};

    insert_before(&header, 0, 5);
    insert_before(&header, 0, 1);
    insert_before(&header, 2, 7);

    print_list(&header);

    insert_after(&header, 2, -6);
    insert_after(&header, 0, -1);
    insert_after(&header, 6, 90);

    printf("\n");
    print_list(&header);

    return 0;
}

void insert_before(Node* headptr, int index, int data)
{
    Node *new_node = (Node*) malloc(sizeof(Node));
    if (new_node == NULL){
        printf("cannot allocate cell");
        exit(1);
    }
    new_node->data = data;

    int i = 0;
    Node* p = headptr->next;
    while(i < index)
    {
        p = p->next;
        i++;
    }

    new_node->next = p;
    new_node->prev = p->prev;
    p->prev->next = new_node;
    p->prev = new_node;
}

void insert_after(Node* headptr, int index, int data)
{
    Node *new_node = (Node*) malloc(sizeof(Node));
    if (new_node == NULL){
        printf("cannot allocate cell");
        exit(1);
    }
    new_node->data = data;

    int i = 0;
    Node* p = headptr->next;
    while(i < index)
    {
        p = p->next;
        i++;
    }

    new_node->next = p->next;
    new_node->prev = p;
    p->next->prev = new_node;
    p->next = new_node;
}