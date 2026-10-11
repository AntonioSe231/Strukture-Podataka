#include <stdio.h>
#include <stdlib.h>

typedef struct _Student {
    char ime[50];
    char prezime[50];
    int bodovi;
} stud;

int main() {
    int brojac = 0;
    char buffer[50] = {0};
    int i = 0;
    int max_br_bodova = 100;

    FILE* fp;
    fp = fopen("popis.txt", "r");

    if (!fp) {
        printf("greska");
        return -1;
    }

    stud* studenti = NULL;
    studenti = (stud*)malloc(brojac * sizeof(stud));

    while (!feof(fp)) {
        brojac++;
        studenti = (stud*)realloc(studenti, brojac * sizeof(stud));
        fscanf(fp, "%s %s %d", studenti[i].ime, studenti[i].prezime, &studenti[i].bodovi);
        i++;
    }

    for (i = 0; i < brojac - 1; i++) {
        printf("%s %s %d %.2f%% \n", studenti[i].ime, studenti[i].prezime, studenti[i].bodovi, (float)studenti[i].bodovi / max_br_bodova * 100);
    }

    if (!fp) {
        free(studenti);
    }

    fclose(fp);

    return 0;
}