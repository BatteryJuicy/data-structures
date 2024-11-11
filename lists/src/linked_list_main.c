#include <stdio.h>
#include "linked_list.h"

int main()
{
    Node* head = NULL;

    insert(&head, 2, 1);
    insert(&head, 2, 2);

    print_list(head);
}