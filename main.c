#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fp = fopen("graf.txt", "r");
    if (!fp) return 1;

    char *line = NULL;
    size_t len = 0;

    // Czytamy całą linię z pliku
    while (getline(&line, &len, fp) != -1) {
        
        // 1. Pobieramy pierwszy "token" (pierwszą liczbę w linii)
        // Jako separatory podajemy spację i znak nowej linii
        char *token = strtok(line, " \n");
        
        if (token != NULL) {
            printf("Węzeł: %s -> Sąsiedzi: ", token);
            
            // 2. Pobieramy kolejne tokeny w pętli
            // Przekazujemy NULL, aby strtok kontynuował pracę na tej samej linii
            token = strtok(NULL, " \n"); 
            
            while (token != NULL) {
                int sasiad = atoi(token); // Zamiana napisu na int
                printf("%d ", sasiad);
                
                token = strtok(NULL, " \n");
            }
            printf("\n");
        }
    }

    free(line);
    fclose(fp);
    return 0;
}