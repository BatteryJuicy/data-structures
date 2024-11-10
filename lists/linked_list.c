#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

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