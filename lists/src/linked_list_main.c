#include <stdio.h>
#include "linked_list.h"

int main()
{
    Node* head = NULL;

    insert(&head, 2, 1);
    insert(&head, 4, 2);
    insert(&head, 4, 7);
    insert(&head, 0, 0);
    print_list(head);
    delete(&head, 7);

    print_list(head);

    printf("test\n");
}