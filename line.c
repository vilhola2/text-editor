#include "text_editor.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Removes the line at 'current_line'
void line_remove(char *buffer, int32_t current_line) {
    char *end = buffer;

    for(int i = 1; i < current_line; ++i) {
        end = strchr(end, '\n') + 1;
    }

    int32_t len = end - buffer;
    end = strchr(end, '\n') + 1;
    memmove(buffer + len, end, strlen(end) + 1);
}

// Adds a line at the end or the beginning. Modes: 'a' -- append, 'i' -- insert 
char *line_add(char *buffer, const char mode) {
    char *newline = str_input(stdin);
    char *new_buffer;
    size_t size = strlen(buffer) + strlen(newline);
    if(size > INT32_MAX) {
        printf("add_line: Buffer is longer than an integer\n");
        free(buffer);
        return NULL;
    }
    switch(mode) {
        case 'a':
            new_buffer = malloc(size + 2);
            sprintf(new_buffer, "%s%s\n", buffer, newline);
            break;
        case 'i':
            new_buffer = malloc(size + 2);
            sprintf(new_buffer, "%s\n%s", newline, buffer);
            break;
        default:
            printf("add_line: Bad mode\n");
            return NULL;
    }

    free(newline);
    free(buffer);
    return new_buffer;
}

// Replaces or adds a line at 'current_line' 
char *line_edit(char *buffer, int32_t current_line, const bool replace_line) {
    char *end = buffer;
    for(int i = 1; i < current_line; ++i) {
        end = strchr(end, '\n') + 1;
    }

    char *newline = str_input(stdin);
    if(!newline) {
        free(buffer);
        printf("edit_line: Newline is NULL\n");
        return NULL;
    }

    int32_t len = end - buffer;
    size_t size = {
        strlen(end) + 
        strlen(newline) + 
        len
    };

    if(size > INT32_MAX) {
        printf("edit_line: Buffer is longer than an integer\n");
        free(newline);
        free(buffer);
        return NULL;
    }

    char *new_buffer = malloc(size + 1);
    if(!new_buffer) {
        free(newline);
        free(buffer);
        printf("edit_line: Failed to malloc new buffer\n");
        return NULL;
    }

    sprintf(new_buffer, "%.*s%s\n%s",
        len,
        buffer,
        newline,
        ((replace_line) ? strchr(end, '\n') + 1 : end)
    );

    free(newline);
    free(buffer);
    return new_buffer;
}
