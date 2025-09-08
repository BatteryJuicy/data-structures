#include <stdio.h>
#include "linked_list.h"

int main()
{
    Node* head = NULL;

    insert(&head, 2, 1);
    insert(&head, 4, 2); //since list has less than 4 elements it will be added at the end.
    insert(&head, 4, 7);
    insert(&head, 0, 0);

    print_list(head);

    delete(&head, 7);
    printf("removed %d\n", 7);

    print_list(head);

    printf("test\n");
}