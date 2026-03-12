#define _GNU_SOURCE // Wymagane dla getline na niektórych systemach
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main() {
    FILE *fp = fopen("graf.txt", "r");
    if (!fp) {
        perror("Błąd otwarcia pliku");
        return 1;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    // Czytamy plik linia po linii
    while ((read = getline(&line, &len, fp)) != -1) {
        printf("Przetwarzam węzeł. Sąsiedzi: ");

        char *ptr = line;
        char *endptr;

        // Wyciągamy wszystkie liczby z przeczytanej linii
        while (1) {
            long val = strtol(ptr, &endptr, 10);
            
            // Jeśli ptr == endptr, oznacza to, że nie znaleziono więcej liczb w linii
            if (ptr == endptr) break;

            printf("[%ld] ", val);

            // Przesuwamy wskaźnik na miejsce, gdzie skończyło się poprzednie czytanie
            ptr = endptr;
        }
        printf("\n");
    }

    free(line); // getline alokuje pamięć, którą musimy zwolnić
    fclose(fp);
    return 0;
}