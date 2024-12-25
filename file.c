#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Returns contents of a file as a string
char *file_read(char *filename) {
    FILE *pF = fopen(filename, "r");
    if(pF == NULL) {
        printf("Failed to open file for reading!\n");
        return NULL;
    }
    fseek(pF, 0, SEEK_END);
    size_t size = ftell(pF);
    rewind(pF);
    char *input = malloc(size);
    fread(input, 1, size, pF);
    fclose(pF);
    return input;
}

// Writes a string to a file
void file_write(char *filename, char *input) {
    FILE *pF = fopen(filename, "w");
    if(pF == NULL) {
        printf("Failed to open file for writing!\n");
        return;
    }
    fwrite(input, strlen(input), 1, pF);
    printf("%s has been written.\n", filename);
    fclose(pF);
}
