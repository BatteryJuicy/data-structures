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
    Districts[index].blanks = 0;
    Districts[index].voids = 0;
    index++;
    printf("D %d %d\n", did, seats);
    printf("    Districts =");
    for (int i = 0; i < index; i++)
    {
        printf(" %d ", Districts[i].did);
    }
    printf("\nDONE\n");

    return 0;
}

/*helper function to find the wanted district with did.
    returns the index of the district in the Districts[] array.
*/
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

int find_party(int pid)
{
    int index = -1;

    for (int i = 0; i < 5; i++)
    {
        if (Parties[i].pid == pid){
            index = i;
            break;
        }
    }
    if (index == -1){
        printf("party with pid %d was not found\n", pid);
        exit(1);
    }
    return index;
}

/*helper function for event S to add the already initialized station s to the district stations list.
    I'm adding the station at the end of the list to make obvious the order in which the input is parsed.
*/
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
    printf("    Sations =");
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
    printf("    Parties =");
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
    printf("    Candidates =");
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
    printf("    Voters =");
    for (struct voter *p = s->voters; p != s->vsentinel; p = p->next)
    {
        printf(" %d ", p->vid);
    }
    printf("\nDONE\n");

    return 0;
}

//helper function to remove voter for event u.
void remove_voter(struct station *s, struct voter *prev)
{
    //remove first voter.
    if (prev == NULL){
        struct voter *temp = s->voters;
        s->voters = temp->next;
        free(temp);
        return;
    }

    struct voter *temp = prev->next;
    prev->next = prev->next->next;
    free(temp);
}

//EVENT U
int unregister_voter(int vid)
{
    for (int i = 0; i < 56; i++)
    {
        for (struct station *s = Districts[i].stations; s; s = s->next)
        {
            s->vsentinel->vid = vid; //setting the sentinel node data to the sought after data.
            struct voter *prev = NULL;
            struct voter *v = s->voters;
            while (v->vid != vid){
                prev = v;
                v = v->next;
            }
            if (v != s->vsentinel){
                remove_voter(s, prev);
                s->registered--;
                printf("U %d\n", vid);
                printf("    %d %d\n", Districts[i].did, s->sid);
                printf("    Voters =");
                for (struct voter *p = s->voters; p != s->vsentinel; p = p->next)
                {
                    printf(" %d ", p->vid);
                }
                printf("\nDONE\n");

                return 0;
            }
        }
        
    }
    printf("couldn't find voter with VID %d\n", vid);
    return 1;
}

//helper function to remove station.
void remove_station(struct district *d, struct station *prevs)
{
    struct station *temp;

    //remove first element.
    if (prevs == NULL)
    {
        temp = d->stations;
        d->stations = d->stations->next;
        free(temp);
        return;
    }

    temp = prevs->next;
    prevs->next = prevs->next->next;
    free(temp);
}

//EVENT E
void delete_empty_stations(void)
{
    printf("E\n");
    for (int i = 0; i < 56; i++)
    {
        struct station *prev = NULL;

        for (struct station *s = Districts[i].stations; s; prev = s, s = s->next)
        {
            if (s->voters == s->vsentinel){
                printf("    %d %d\n", s->sid, Districts[i].did);
                remove_station(&Districts[i], prev);
            }
        }
    }
    printf("DONE\n");
}

//helper function to swap candidates until the list is sorted for event v.
void swapNsort_candidates(struct district *d, struct candidate *c)
{
    //if c is the first element.
    if (d->candidates == c)
        return;
    //if the list needs to be sorted then swap c with its previous node until sorted.
    while (c->prev != NULL && c->votes > c->prev->votes)
    {
        //if c is the second element.
        if (d->candidates->next == c){
            d->candidates = c;
        }
        //if c is 3rd or later element.
        else{
            c->prev->prev->next = c;
        }
        c->prev->next = c->next;
        if (c->next != NULL)
            c->next->prev = c->prev;
        c->next = c->prev;
        struct candidate *temp = c->prev;
        c->prev = c->prev->prev;
        temp->prev = c;
    }

}

//EVENT V
int vote(int vid, int sid, int cid)
{
    struct district *d = NULL;
    struct station *s = NULL;

    for (int i = 0; i < 56; i++)
    {
        d = &Districts[i];
        s = d->stations;
        while (s != NULL)
        {
            if (s->sid == sid)
                break;

            s = s->next;
        }
        if (s != NULL && s->sid == sid)
            break;
    }

    if (s == NULL) {
        printf("Station with SID %d not found\n", sid);
        return 1;
    }

    s->vsentinel->vid = vid; //setting the sentinel node data to the sought after data.

    struct voter *v = s->voters;

    while (v->vid != vid)
        v = v->next;

    //if the voter was found
    if (v != s->vsentinel)
    {
        v->voted = 1;

        if (cid == 0)
            d->blanks++;
        else if (cid == 1)
            d->voids++;
        //if he voted for someone, itereate candidates list until he is found 
        //and then update the votes and the list to retain it's discending order of votes.
        else{
            for (struct candidate *c = d->candidates; c; c = c->next)
            {
                if (c->cid == cid){
                    c->votes++;
                    swapNsort_candidates(d, c);
                    break;
                }
            }
        }
        printf("V %d %d %d\n", vid, sid, cid);
        printf("    District = %d\n", d->did);
        printf("    Candidate votes =");

        struct candidate *c = d->candidates;
        while (c != NULL && c->next != NULL)
        {
            printf(" (%d, %d), ", c->cid, c->votes);
            c = c->next;
        }
        printf(" (%d, %d)\n", c->cid, c->votes);
        printf("    Blanks = %d\n", d->blanks);
        printf("    Voids = %d\n", d->voids);
        printf("DONE\n");

        return 0;
    }

    printf("couldn't find voter with VID %d\n", vid);
    return 1;
}

//helper function to add candidate to the sorted list of candidates of a party for event m.
void add_party_candidate(struct party *p, struct candidate *c)
{
    struct candidate *prevq = NULL;
    struct candidate *q = p->elected;
    while(q != NULL && q->votes >= c->votes)
    {
        prevq = q;
        q = q->next;
    }
    
    //insert at the start of the list. (c has the most votes of the party candidates)
    if (prevq == NULL)
    {
        c->next = q;
        p->elected = c;
        return;
    }
    //instert at the middle or end of the list.
    c->next = q;
    prevq->next = c;

}

//EVENT M
void count_votes(int did)
{
    //pointer to district with did.
    struct district *d = &Districts[find_district(did)];
    //array of the votes of each party.
    int party_votes[5] = {0};
    int party_seats[5] = {0};
    double metro = 0;

    for (int i = 0; i < 5; i++)
    {
        struct candidate *c = d->candidates;
        while (c != NULL && c->votes > 0)
        {
            if (c->pid == Parties[i].pid){
                party_votes[i] += c->votes;
            }
            c = c->next;
        }
        metro += party_votes[i];
    }
    if (d->seats <= 0){
        printf("district seats have an invalid value. Exiting...\n");
        exit(1);
    }
    else{
        metro = metro/(double)d->seats;
    }
    if (metro != 0){
        for (int i = 0; i < 5; i++)
        {
            party_seats[i] = party_votes[i]/metro;        
        }
    }
    
    struct candidate *c = d->candidates;
    while (c!=NULL)
    {   int party_index = find_party(c->pid);

        if (party_seats[party_index] > 0 && c->elected == 0)
        {
            c->elected = 1;
            d->allotted++;
            Parties[party_index].nelected++;
            party_seats[party_index]--;
            add_party_candidate(&Parties[party_index], c);
        }
        c = c->next;
    }
}

//EVENT G
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