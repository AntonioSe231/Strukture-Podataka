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

int insertAfterP(char* name, char* lname, int year, char* tlname, Position P) {
    Position target = findLName(tlname, P);

    if (target == NULL)
        return -1;

    return insertBegin(name, lname, year, target);
}

int insertBeforeP(char* name, char* lname, int year, char* tlname, Position P) {
    Position target = findLName(tlname, P);

    if (target == NULL)
        return -1;

    while (P->next != target)
        P = P->next;

    insertBegin(name, lname, year, P);

    return 0;
}

int sort(char* lname, Position head) {
    Position P = head->next;
    Position Q = head;

    while (P != NULL && P->next != NULL) {
        if (strcmp(P->lname, P->next->lname) > 0) {
            Position temp = P->next;
            Q->next = temp;
            P->next = temp->next;
            temp->next = P;
            Q = head;
            P = head->next;
        } else {
            Q = P;
            P = P->next;
        }
    }

    return 0;
}

int writeFile(char* fn, Position head) {
    FILE* fp = fopen(fn, "w");
    Position P = head->next;

    if (fp == NULL)
        return -1;

    while (P != NULL) {
        fprintf(fp, "%s %s %d\n", P->name, P->lname, P->year);
        P = P->next;
    }

    fclose(fp);

    return 0;
}

int readFile(char* fn, Position head) {
    FILE* fp = fopen(fn, "r");
    char name[50];
    char lname[50];
    int year;

    if (fp == NULL)
        return -1;

    while (head->next != NULL) {
        Position temp = head->next;
        head->next = temp->next;
        free(temp);
    }

    while (fscanf(fp, "%49s %49s %d", name, lname, &year) == 3)
        insertEnd(name, lname, year, head);

    fclose(fp);

    return 0;
}

int main() {
    Person head = {.name = "", .lname = "", .year = 0, .next = NULL};
    Position P = &head;
    Position Q = NULL;

    insertBegin("Ime1", "Prezime1", 2000, P);
    insertEnd("Ime2", "Prezime2", 2001, P);
    insertAfterP("Marko", "Kovac", 1999, "Horvat", P);
    insertBeforeP("Petra", "Babic", 2002, "Horvat", P);

    sort("Prezime1", P);
    writeFile("popis.txt", P);

    for (Position Q = P->next; Q != NULL; Q = Q->next)
        printf("%s %s. Born: %d\n", Q->name, Q->lname, Q->year);

    Q = findLName("Prezime1", P);

    if (Q != NULL)
        printf("Found: %s %s\n", Q->name, Q->lname);
    deletePerson("Prezime1", P);

    if (readFile("popis.txt", P) == 0) {
        printf("\nLista procitana iz datoteke:\n");
        for (Q = P->next; Q != NULL; Q = Q->next)
            printf("%s %s. Born: %d\n", Q->name, Q->lname, Q->year);
    }

    while (P->next != NULL) {
        Q = P->next;
        P->next = Q->next;
        free(Q);
    }

    return 0;
}