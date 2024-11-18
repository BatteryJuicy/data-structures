#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "elections.h"

extern struct district Districts[56];
extern struct party Parties[5];
extern struct parliament Parliament;

//EVENT A
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

//EVENT D
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

//helper function to find the wanted district with did.
int find_district(int did)
{
    int index = -1;

    for (int i = 0; i < 56; i++)
    {
        if (Districts[i].did == did){
            index = i;
            break;
        }
    }
    if (index == -1){
        printf("district with did %d was not found\n", did);
        exit(1);
    }
    return index;
}

//helper function for event S to add the already initialized station s to the district stations list.
void add_station(struct district *d, struct station *s)
{
    struct station* prevp = NULL;
    struct station* p = d->stations;
    while(p != NULL)
    {
        prevp = p;
        p = p->next;
    }
    
    //if list is empty.
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

//EVENT S
int create_station(int sid, int did)
{
    int district_index = find_district(did);

    //creating the station.
    struct station *s = (struct station*) malloc(sizeof(struct station));
    if (s == NULL){
        printf("couldn't allocate station with SID %d at district with DID %d\n", sid, did);
        exit(1);
    }
    //init station data
    s->sid = sid;
    s->registered = 0;
    //creating the sentinel node.
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

//EVENT P
void create_party(int pid)
{
    static int party_index = 0;

    Parties[party_index].pid = pid;
    party_index++;

    printf("P %d\n", pid);
    printf("Parties =");
    for (int i = 0; i < party_index; i++)
    {
        printf(" %d ", Parties[i].pid);
    }
    printf("\nDONE\n");
}

//helper function for event C to add the initialized candidate c to the doubly linked list candidates of the distric d.
void add_candidate(struct district *d, struct candidate *c)
{
    struct candidate* prevp = NULL;
    struct candidate* p = d->candidates;
    while(p != NULL)
    {
        prevp = p;
        p = p->next;
    }
    
    //if list is empty.
    if (prevp == NULL)
    {
        c->next = NULL;
        d->candidates = c;
        c->prev = NULL;
        return;
    }

    //otherwise if the candidate is at the end.
    c->next = NULL;
    prevp->next = c;
    c->prev = prevp;
}

//EVENT C
int register_candidate(int cid, int did, int pid)
{
    int district_index = find_district(did);

    //creating candidate.
    struct candidate *c = (struct candidate*) malloc(sizeof(struct candidate));

    if (c == NULL){
        printf("couldn't allocate candidate with CID %d from the party with PID %d at the district with DID %d\n", cid, did, pid);
        exit(1);
    }
    //initialized candidate data.
    c->cid = cid;
    c->pid = pid;
    c->votes = 0;
    c->elected = 0;
    
    //adding the candidate to the end of the candidates list of district d.
    add_candidate(&Districts[district_index], c);

    printf("C %d %d %d\n", cid, did, pid);
    printf("Candidates =");
    for (struct candidate *p = Districts[district_index].candidates; p; p = p->next)
    {
        printf(" %d ", p->cid);
    }
    printf("\nDONE\n");

    return 0;
}

//helper function to add voter at the end of voters list for event R.
void add_voter(struct station *s, struct voter *v)
{
    struct voter *prevp = NULL;
    struct voter *p = s->voters;

    while (p != s->vsentinel)
    {
        prevp = p;
        p = p->next;
    }

    //list is empty.
    if(prevp == NULL)
    {
        s->voters = v;
        v->next = s->vsentinel;
        return;
    }

    //otherwise if the voter is at the end.
    v->next = s->vsentinel;
    prevp->next = v;
}

//EVENT R
int register_voter(int vid, int did, int sid)
{
    int district_index = find_district(did);

    //finding the station with sid.
    struct station *s = NULL;
    for (struct station* p = Districts[district_index].stations; p; p = p->next)
    {
        if (p->sid == sid){
            s = p;
            break;
        }
    }
    if (s == NULL){
        printf("couldn't find station with sid %d", sid);
        exit(1);
    }
    
    //creating voter.
    struct voter *v = (struct voter *) malloc(sizeof(struct voter));
    if (v == NULL){
        printf("couldn't allocate voter with VID %d to station with SID %d in district with SID %d\n", vid, sid, did);
        exit(1);
    }

    //initializing voter data.
    v->vid = vid;

    add_voter(s, v);
    s->registered++;

    printf("R %d %d %d\n", vid, did, sid);
    printf("Voters =");
    for (struct voter *p = s->voters; p != s->vsentinel; p = p->next)
    {
        printf(" %d ", p->vid);
    }
    printf("\nDONE\n");

    return 0;
}

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