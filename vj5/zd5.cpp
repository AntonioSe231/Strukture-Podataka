#include <stdio.h>
#include <stdlib.h>

typedef struct _Stog* Position;
typedef struct _Stog {
    double num;
    Position next;
} Stog;

int Push(Position head, double num) {
    Position newP = (Position)malloc(sizeof(Stog));

    if (newP == NULL)
        return -1;

    newP->num = num;
    newP->next = head->next;
    head->next = newP;

    return 0;
}

int Pop(Position head, double* result) {
    Position p = head->next;
    Position q = NULL;
    double a, b;

    if (p == NULL || p->next == NULL)
        return -1;

    a = p->next->num;
    b = p->num;

    switch ((char)*result) {
        case '+': 
            *result = a + b;
            break;
        case '-': 
            *result = a - b;
            break;
        case '*': 
            *result = a * b;
            break;
        case '/':
            if (b == 0)
                return -1;
            *result = a / b;
            break;
        default:
            return -1;
    }

    q = p->next->next;

    free(p->next);
    free(p);

    return Push(head, *result);
}

int main() {
    Stog head = {0, NULL};
    Position P = &head;
    Position q = NULL;

    FILE* fp = fopen("postfix.txt", "r");
    char buffer[2];
    char* end;
    double num, result;

    if (fp == NULL)
        return -1;

    while (fscanf(fp, "%s", buffer) == 1) {
        num = strtod(buffer, &end);

        if (*end == '\0') {
            if (Push(P, num) == -1)
                return -1;
        }
        else if (buffer[1] == '\0' && (buffer[0] == '+' || buffer[0] == '-' || buffer[0] == '*' || buffer[0] == '/')) {
            result = buffer[0];

            if (Pop(P, &result) == -1) {
                printf("Greska u izrazu!\n");
                fclose(fp);
                return -1;
            }
        }
        else {
            printf("Krivi unos!\n");
            fclose(fp);
            return -1;
        }
    }

    fclose(fp);

    if (P->next == NULL || P->next->next != NULL) {
        printf("Greska u izrazu!\n");
        return -1;
    }

    printf("Rezultat: %.2f\n", P->next->num);

    while (P->next != NULL) {
        q = P->next;
        P->next = q->next;
        free(q);
    }

    return 0;
}