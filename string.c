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
        printf("Initial allocation failed!\n");
        return NULL;
    }

    while((ch = fgetc(stream)) != EOF && ch != '\n') {
        buffer[len++] = ch;
        if(len == bufsize) {
            char *temp = realloc(buffer, (bufsize += 16));
            if(!temp) {
                printf("Realloc failed!\n");
                free(buffer);
                return NULL;
            }
            buffer = temp;
        }
    }

    if(len < bufsize) {
        char *temp = realloc(buffer, len + 1);
        if(!temp) {
            printf("Realloc failed!\n");
            free(buffer);
            return NULL;
        }
        buffer = temp;
    }

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

// Counts all newline characters in a string
int32_t str_get_line_count(char *input) {
    char *buffer = input;
    int line_count = 0;
    while((buffer = strchr(buffer, '\n')) != NULL) {
        ++buffer;
        ++line_count;
    }
    return line_count;
}
