#include "text_editor.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Reads input from a given file stream and returns a heap-allocated string
char *str_input(FILE *stream) {
    int ch;
    size_t len = 0;
    size_t bufsize = 16;
    char *buffer = malloc(bufsize);
    if(!buffer) {
        printf("str_input: Malloc failed\n");
        return NULL;
    }

    while((ch = fgetc(stream)) != EOF && ch != '\n') {
        buffer[len++] = ch;
        if(len + 1 == bufsize) {
            char *temp = realloc(buffer, (bufsize += 16));
            if(!temp) {
                printf("str_input: Realloc failed\n");
                free(buffer);
                return NULL;
            }
            buffer = temp;
        }
    }

    printf("bufsize: %zu\nlen: %zu\n", bufsize, len);

    buffer[len] = '\0';
    return buffer;
}

// Prints a string with line numbers and counts newlines
void str_print(char *input, int32_t *line_count) {
    *line_count = 0;
    char *start = input;
    char *end;

    putchar('\n');
    while((end = strchr(start, '\n')) != NULL) {
        printf("%d  %.*s\n", ++(*line_count), (int)(end - start), start);
        start = end + 1;
    }
    putchar('\n');
}
