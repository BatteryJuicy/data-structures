#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "elections.h"

extern struct district Districts[56];
extern struct party Parties[5];
extern struct parliament Parliament;

void announce_elections()
{
    for (int i = 0; i < 56; i++)
    {
        Districts[i].did = -1;
        Districts[i].seats = -1;
        Districts[i].allotted = -1;
        Districts[i].blanks = -1;
        Districts[i].voids = -1;
        Districts[i].stations = NULL;
        Districts[i].candidates = NULL;
    }
    for (int i = 0; i < 5; i++)
    {
        Parties[i].pid = -1;
        Parties[i].nelected = -1;
        Parties[i].elected = NULL;
    }

    Parliament.members = NULL;    
    printf("A\nDONE\n");

}

int create_district(int did, int seats)
{
    Districts[did].did = did;
    Districts[did].seats = seats;
    Districts[did].allotted = 0;

    printf("D %d %d\n", did, seats);
    printf("Districts =");
    for (int i = 0; i < did; i++)
    {
        printf(" %d ", did);
    }
    printf("\nDONE\n");
    
}