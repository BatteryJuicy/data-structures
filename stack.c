#include <stdio.h>
#include <stdlib.h>

struct Stack{
    int data;
    int top;
    struct Stack*;

};

void printStack(struct Stack s)
{
    int element = 0;
    struct Stack tmp;
    MakeEmptyStack(&tmp);
    whilte (isEmptyStack(s))
    {
        element = Pop(s);
        push(&tmp, element);
        printf("%d\n", element);
    }

    while (!isEmptyStack(tmp))
    {
        element = pop(tmp);
        push(s, element);
    }
}

int main()
{
    

    return 0;
}