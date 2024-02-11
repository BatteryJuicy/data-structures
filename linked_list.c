#include <stdio.h>
#include <stdlib.h>

typedef struct list{
    int data;
    struct list *next;
}cell;

void add(cell*, int);

int main(int argc, char **argv)
{
    cell head = {0};

    cell* index = head.next;
    for (int i = 1; i < 10; i++)
    {
        add(index, i);
        index = index->next;
    }
    printf("A\n");
    for (cell* pos = head.next; pos; pos = pos->next)
    {
        printf("%d", pos->data);
    }
    printf("\nB33\n");
    for (cell* pos = head.next; pos; pos = pos->next)
    {
        free(pos);
    }
    printf("C\n");
}

void add(cell* prev_cell, int new_data)
{
    cell* new_cell = (cell*) malloc(sizeof(cell));
    if(new_cell == NULL)
    {
        printf("cannot allocate memory");
        exit(1);
    }
    new_cell->data = new_data;
    new_cell->next = prev_cell->next;
    prev_cell->next = new_cell;
}