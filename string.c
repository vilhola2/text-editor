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

// Reads a string from the user
void str_input(char *target, size_t *size) {
    while(1) {
        if(fgets(target, *size, stdin) == NULL) {
            printf("Failed to read input (NULL)\n");
            return; // early exit on failure
        }
        if(strchr(target, '\n') == NULL) {
            printf("Input is too long! Try again.\n");
            clear_input_buffer();
        } else {
            target[strcspn(target, "\n")] = '\0';
            break;
        }
    }
}

// Prints a string with line numbers and writes the line count into the callers variable
void str_print(char *input, int32_t *line_number) {
    *line_number = 1;
    char *start = input;
    char *end;

    putchar('\n');
    while((end = strchr(start, '\n')) != NULL) {
        printf("%d  %.*s\n", (*line_number)++, (int)(end - start), start);
        start = end + 1;
    }
    if(*start != '\0') {
        printf("%d  %s\n", *line_number, start);
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
