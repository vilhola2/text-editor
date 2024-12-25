#include "text_editor.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int32_t str_get_line_count(char *input) {
    char *buffer = input;
    int line_count = 0;
    while((buffer = strchr(buffer, '\n')) != NULL) {
        ++buffer;
        ++line_count;
    }
    return line_count;
}

// Magic user input reading function
char *str_input(size_t *bufsize) {
    int ch;
    size_t len = 0;
    char *buffer = malloc(*bufsize);
    if(!buffer) return NULL;
    while((ch = fgetc(stdin)) != EOF && ch != '\n') {
        buffer[len++] = ch;
        if(len == *bufsize) {
            char *temp = realloc(buffer, (*bufsize += 16));
            if(!temp) {
                free(buffer);
                return NULL;
            }
        }
    }
    buffer[len++] = '\0';
    return realloc(buffer, len);
}

// Prints a string with line numbers and writes the line count into the callers variable
void str_print(char *input, int32_t *line_number) {
    *line_number = 0;
    char *start = input;
    char *end;

    putchar('\n');
    while((end = strchr(start, '\n')) != NULL) {
        printf("%d  %.*s\n", ++(*line_number), (int)(end - start), start);
        start = end + 1;
    }
    if(*start != '\0') {
        printf("%d  %s\n", ++(*line_number), start);
    }
    putchar('\n');
}

// Modifies a string to be only 1 line ( Unused for now )
void str_reduce(char *input) {
    if(strchr(input, '\n') == NULL) return;
    int i = 0;
    while(1) {
        if(input[i] == '\n') break;
        ++i;
    }
    input[i+1] = '\0';
}
