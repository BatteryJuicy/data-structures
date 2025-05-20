#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h> //library to allow variadic functions (variable number of parameters).

#define  TABLE_SIZE 10
#define MAX_NAME 25

typedef struct student{
    int am;
    char* name;
    int year;
    struct student* next;
}student;

void print_student(student* st)
{
    printf("name: %s\n\t\tAM: %d\n\t\tYear: %d\n\t\t", st->name, st->am, st->year);
}

int list_length(student* head)
{
    int length = 0;
    for (student* p = head; p; p = p->next)
    {
        length ++;
    }
    return length;
}

student* create_student(int am, char* name, int year)
{
    student* result = malloc(sizeof(student));
    
    result->am = am;
    result-> name = name;
    result->year = year;

    return result;
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

void init_hashtable(student* table_ptr[])
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        table_ptr[i] = NULL;
    }
}

//takes as parameters a hashtable and an optional string to specify printing mode.
//to print each student in detail the second argument should be "detail". Otherwise the default mode will be used.
void print_table(student* table[], ...)
{
    const char* mode = "default";

    va_list args;
    va_start(args, table);
    const char* passed_mode = va_arg(args, const char*);
    if (passed_mode != NULL)
        mode = passed_mode;
    va_end(args);

    printf("START\n");
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        printf("\t%d\t", i);
        if (table[i] != NULL)
        {
            student* tmp = table[i];
            int length = list_length(table[i]);
            for (int j = 0; j < length; j++)
            {
                if (!strcmp(mode, "detail")){
                    print_student(tmp);
                    printf("\n\t\t");
                }
                else{
                    printf("%s ", tmp->name);
                }
                tmp = tmp->next;
            }
            printf("\n");
        }
        else
        {
            if (!strcmp(mode, "detail"))
                printf("----\n\n\n");
            else
                printf("----\n");
        }
    }
    printf("END\n");
}

//if it returns NULL it means there isn't any student with that name.
student* return_student(student* table[], char name[])
{
    int index = hash(name);
    
    student* result = table[index];

    while (result != NULL && strcmp(result->name, name)) //while the student hasn't been found and the we aren't at the end of the list.
    {
        result = result->next;
    }
    return result;
}

bool hashtable_insert(student* table[], student* p)
{
    if (p == NULL) return false;
    int index = hash(p->name);
    if (table[index] == NULL)
    {
        table[index] = p;
    }
    else
    {
        student* first = table[index];

        p->next = table[index];
        table[index] = p;
    }
    return true;
}

 
bool hashtable_delete(student *table[], char name[])
{
    int index = hash(name);
    
    student* prev_student = NULL;
    student* result = table[index];

    while (result != NULL && strcmp(result->name, name))
    {
        prev_student = result;
        result = result->next;
    }
    if (result == NULL)
        return false;
    if (prev_student == NULL) // remove the first student
    {
        table[index] = result->next;
    }
    else{
        prev_student->next = result->next;
    }
    free(result);
    return true;
    
}

int main()
{
    student* hash_table[TABLE_SIZE];

    init_hashtable(hash_table);

    print_table(hash_table);

    student* Themis = create_student(5101, "Themis",2023);
    student* Alexandros = create_student(5555, "Alexandros", 2023);
    student* giorgos = create_student(6969, "Giorgos", 2022);
    student* Panagiotis = create_student(5684, "Panagiotis", 2020);
    student* Platonas = create_student(4458, "Platonas", 1999);
    student* Mixalis = create_student(5932, "Mixalis", 2008);
    student* Thanos = create_student(2167, "Thanos", 2012);
    student* Giannis = create_student(6547, "Giannis", 1998);
    student* Marinos = create_student(9199, "Marinos", 1996);
    student* Kostas = create_student(9367, "Kostas", 1987);
    student* Ektoras = create_student(1587, "Ektoras", 2016);
    student* Dimitris = create_student(6431, "Dimitris", 2019);
    student* Sokratis = create_student(9516, "Sokratis", 2001);

    hashtable_insert(hash_table, Themis);
    hashtable_insert(hash_table, Alexandros);
    hashtable_insert(hash_table, giorgos);
    hashtable_insert(hash_table, Panagiotis);
    hashtable_insert(hash_table, Platonas);
    hashtable_insert(hash_table, Mixalis);
    hashtable_insert(hash_table, Thanos);
    hashtable_insert(hash_table, Giannis);
    hashtable_insert(hash_table, Marinos);
    hashtable_insert(hash_table, Kostas);
    hashtable_insert(hash_table, Dimitris);
    hashtable_insert(hash_table, Sokratis);


    print_table(hash_table, "detail");

    print_table(hash_table);

    if(hashtable_delete(hash_table, "Sokratis")){
        printf("delted <Sokratis>\n");
    }
    else{
        printf("couldn't delete <Sokratis>\n");
    }

    print_table(hash_table);

    hashtable_delete(hash_table, "Thanos");
    hashtable_delete(hash_table, "Platonas");

    print_table(hash_table);
}