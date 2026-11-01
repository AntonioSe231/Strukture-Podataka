#include <stdio.h>
#include <stdlib.h>

typedef struct Poly* Position;

typedef struct Poly {
    int koef;
    int pow;
    Position next;
} Polynom;

Position newPoly(int koef, int pow) {
    Position newP = (Position)malloc(sizeof(Polynom));

    if (newP == NULL)
        return NULL;

    newP->koef = koef;
    newP->pow = pow;
    newP->next = NULL;

    return newP;
}

int insertBegin(Position q, Position newP) {
    newP->next = q->next;
    q->next = newP;

    return 0;
}

int insertSorted(Position q, Position newP) {
    if (q->next == NULL)
        return insertBegin(q, newP);

    if (newP->pow > q->next->pow)
        return insertBegin(q, newP);

    if (newP->pow < q->next->pow)
        return insertSorted(q->next, newP);

    q->next->koef += newP->koef;
    free(newP);

    return 0;
}

int deletePoly(Position head) {
    Position temp;

    while (head->next != NULL) {
        temp = head->next;
        head->next = temp->next;
        free(temp);
    }

    return 0;
}

int printPoly(Position head) {
    Position P = head->next;

    if (P == NULL)
        printf("0");

    while (P != NULL) {
        printf("%dx^%d ", P->koef, P->pow);
        P = P->next;
    }

    printf("\n");

    return 0;
}

int readFile(char* fn, Position head) {
    FILE* fp = fopen(fn, "r");
    int buffer[2];
    Position newP;

    if (fp == NULL)
        return -1;

    deletePoly(head);

    while (fscanf(fp, "%d %d", &buffer[0], &buffer[1]) == 2) {
        newP = newPoly(buffer[0], buffer[1]);

        if (newP == NULL) {
            fclose(fp);
            return -1;
        }

        insertSorted(head, newP);
    }

    fclose(fp);

    return 0;
}

int zbrajanje(Position head, Position headF, Position headS) {
    Position P, newP;

    P = headF->next;

    while (P != NULL) {
        newP = newPoly(P->koef, P->pow);

        if (newP == NULL)
            return -1;

        insertSorted(head, newP);
        P = P->next;
    }

    P = headS->next;

    while (P != NULL) {
        newP = newPoly(P->koef, P->pow);

        if (newP == NULL)
            return -1;

        insertSorted(head, newP);
        P = P->next;
    }

    P = head;

    while (P->next != NULL) {
        if (P->next->koef == 0) {
            Position temp = P->next;
            P->next = temp->next;
            free(temp);
        }
        else
            P = P->next;
    }

    return 0;
}

int mnozenje(Position head, Position headF, Position headS) {
    Position P, Q, newP;

    P = headF->next;

    while (P != NULL) {
        Q = headS->next;

        while (Q != NULL) {
            newP = newPoly(P->koef * Q->koef, P->pow + Q->pow);

            if (newP == NULL)
                return -1;

            insertSorted(head, newP);
            Q = Q->next;
        }

        P = P->next;
    }

    P = head;

    while (P->next != NULL) {
        if (P->next->koef == 0) {
            Position temp = P->next;
            P->next = temp->next;
            free(temp);
        }
        else
            P = P->next;
    }

    return 0;
}

int main() {
    Polynom head = {0, 0, NULL};
    Polynom headF = {0, 0, NULL};
    Polynom headS = {0, 0, NULL};

    if (readFile("polinom1.txt", &headF) == -1)
        return -1;

    if (readFile("polinom2.txt", &headS) == -1)
        return -1;

    if (zbrajanje(&head, &headF, &headS) == -1)
        return -1;

    printf("Zbroj: ");
    printPoly(&head);

    deletePoly(&head);

    if (mnozenje(&head, &headF, &headS) == -1)
        return -1;

    printf("Umnozak: ");
    printPoly(&head);

    deletePoly(&head);
    deletePoly(&headF);
    deletePoly(&headS);

    return 0;
}