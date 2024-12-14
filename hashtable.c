#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define  TABLE_SIZE 10
#define MAX_NAME 20

typedef struct student{
    int am;
    char name[MAX_NAME];
    int year;
    struct student* next;
}student;

int list_length(student* head)
{
    int length = 0;
    for (student* p = head; p; p = p->next)
    {
        length ++;
    }
    return length;
}

unsigned int hash(char name[])
{
    int len = strnlen(name, MAX_NAME);
    unsigned int hash_result = 0;
    for (int i = 0; i < len; i++)
    {
        hash_result += name[i];
        hash_result *= name[i];
    }
    hash_result *= len;
    
    return hash_result % TABLE_SIZE;    
}

void init_hash_table(student* table_ptr[])
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        table_ptr[i] = NULL;
    }
    
}

void print_table(student* table[])
{
    printf("START\n");
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        printf("\t%d\t", i);
        if (table[i] != NULL)
        {
            student* tmp = table[i];
            int length = list_length(table[i]);
            for (int i = 0; i < length; i++)
            {
                printf("%s ", tmp->name);
                tmp = tmp->next;
            }
            printf("\n");
        }        
        else
        {
            printf("----\n");
        }
    }
    printf("END\n");
}

bool hash_table_insert(student* table[], student* p)
{
    if (p == NULL) return false;
    int index = hash(p->name);
    if (table[index] == NULL)
    {
        table[index] = p;
        return true;
    }
    else
    {
        student* first = table[index];

        p->next = table[index];
        table[index] = p;
    }
}

int main()
{
    student* hash_table[TABLE_SIZE];
    init_hash_table(hash_table);

    print_table(hash_table);

    student andreas = {.am=5401, .name="Andreas", .year=2023};
    student aggelos = {.am=5555, .name="Aggelos", .year=2023};
    student giorgos = {.am=6969, .name="Giorgis", .year=2022};

    hash_table_insert(hash_table, &andreas);
    hash_table_insert(hash_table, &aggelos);
    hash_table_insert(hash_table, &giorgos);

    print_table(hash_table);
}