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
    static int index = 0;

    Districts[index].did = did;
    Districts[index].seats = seats;
    Districts[index].allotted = 0;
    index++;
    printf("D %d %d\n", did, seats);
    printf("Districts =");
    for (int i = 0; i < index; i++)
    {
        printf(" %d ", Districts[i].did);
    }
    printf("\nDONE\n");

    return 0;
}

//helper function for event S to make the code easier to read.
void add_station(struct district *d, struct station *s)
{
    struct station* prevp = NULL;
    struct station* p = d->stations;
    while(p != NULL)
    {
        prevp = p;
        p = p->next;
    }
    
    //if list is empty or we need to add a node at the start of the list.
    if (prevp == NULL)
    {
        s->next = d->stations;
        d->stations = s;
        return;
    }

    //otherwise if the station is at the end.
    s->next = prevp->next;
    prevp->next = s;

}

int create_station(int sid, int did)
{
    int district_index = -1;

    for (int i = 0; i < 56; i++)
    {
        if (Districts[i].did == did){
            district_index = i;
            break;
        }
    }
    if (district_index == -1){
        printf("district with did %d was not found\n", did);
        exit(1);
    }

    //creating the station.
    struct station *s = (struct station*) malloc(sizeof(struct station));
    if (s == NULL){
        printf("couldn't allocate station\n");
        exit(1);
    }
    //init station data
    s->sid = sid;
    s->registered = 0;
    //creatin the sentinel node.
    struct voter *vSentinel = (struct voter*) malloc(sizeof(struct voter));
    vSentinel->next = NULL;
    s->vsentinel = vSentinel;
    s->voters = vSentinel;
    
    add_station(&Districts[district_index], s);

    printf("S %d %d\n", sid, did);
    printf("Sations =");
    for (struct station *p = Districts[district_index].stations; p; p = p->next)
    {
        printf(" %d ", p->sid);
    }
    printf("\nDONE\n");

    return 0;
}

// void create_party(int pid)
// {

// }

// int register_candidate(int cid, int did, int pid)
// {

// }

// int register_voter(int vid, int did, int sid)
// {

// }

// int unregister_voter(int vid)
// {

// }

// int vote(int vid, int sid, int cid)
// {

// }

// void count_votes(int did)
// {

// }

// void form_government(void)
// {

// }

// void form_parliament(void)
// {

// }

// void print_district(int did)
// {

// }

// void print_station(int sid, int did)
// {

// }

// void print_party(int pid)
// {

// }

// void print_parliament(void)
// {

// }