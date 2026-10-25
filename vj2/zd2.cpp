#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct _Person* Position;

typedef struct _Person {
    char name[50];
    char lname[50];
    int year;
    Position next;
} Person;

int insertAfter(Position P, Position newP) {
    newP->next = P->next;
    P->next = newP;

    return 0;
}

int insertBegin(char* name, char* lname, int year, Position P) {
    Position newPerson = NULL;

    newPerson = (Position)malloc(sizeof(Person));
    if (newPerson == NULL)
        return -1;

    strcpy(newPerson->name, name);
    strcpy(newPerson->lname, lname);
    newPerson->year = year;
    newPerson->next = NULL;

    insertAfter(P, newPerson);

    return 0;
}

int insertEnd(char* name, char* lname, int year, Position P) {
    Position newPerson = NULL;

    newPerson = (Position)malloc(sizeof(Person));
    if (newPerson == NULL)
        return -1;

    strcpy(newPerson->name, name);
    strcpy(newPerson->lname, lname);
    newPerson->year = year;
    newPerson->next = NULL;

    while (P->next != NULL)
        P = P->next;
    
    insertAfter(P, newPerson);

    return 0;
}

Position findLName(char* lname, Position P) {
    Position Q = P->next;

    for (Q; Q != NULL; Q = Q->next)
        if (strcmp(Q->lname, lname) == 0)
            return Q;

    return NULL;
}

int deletePerson(char* lname, Position P) {
    Position prev = P;
    Position curr = prev->next;

    curr = findLName(lname, prev);

    if (curr == NULL)
        return -1;

    while (prev->next != curr)
        prev = prev->next;

    prev->next = curr->next;

    free(curr);

    return 0;
}

int main() {
    Person head = {.name = "", .lname = "", .year = 0, .next = NULL};
    Position P = &head;
    Position Q = NULL;

    insertBegin("Ime1", "Prezime1", 2000, P);
    insertEnd("Ime2", "Prezime2", 2001, P);

    for (Q = P->next; Q != NULL; Q = Q->next)
        printf("%s %s. Born: %d\n", Q->name, Q->lname, Q->year);

    Q = findLName("Prezime1", P);
    if (Q != NULL)
        printf("Found: %s %s\n", Q->name, Q->lname);
    deletePerson("Prezime1", P);

    while (P->next != NULL) {
        Q = P->next;
        P->next = Q->next;
        free(Q);
    }

    return 0;
}
