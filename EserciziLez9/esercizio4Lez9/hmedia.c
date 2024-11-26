#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <percorso_del_file_CSV>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *path = argv[1];

    // Apri il file CSV utilizzando il percorso fornito
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        perror("Errore nell'apertura del file");
        return EXIT_FAILURE;
    }

    char line[MAX_LINE_LENGTH];
    int line_number = 0;
    double sum = 0.0;
    int count = 0;

    while (fgets(line, sizeof(line), file)) {
        line_number++;
        if (line_number == 1) {
            continue; // Salta la prima riga
        }

        char *token;
        int field = 0;
        token = strtok(line, ",");
        while (token != NULL) {
            field++;
            if (field == 5) {
                sum += atof(token);
                count++;
                break;
            }
            token = strtok(NULL, ",");
        }
    }

    fclose(file);

    if (count > 0) {
        double average = sum / count;
        printf("La media del quinto campo è: %f\n", average);
    } else {
        printf("Nessun dato disponibile per calcolare la media.\n");
    }

    return EXIT_SUCCESS;
}
