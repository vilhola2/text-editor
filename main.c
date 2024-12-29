#include "text_editor.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main_loop(char *filename);
void print_help(void);
void remove_line(char *buffer, int32_t current_line);
char *add_empty_line(char *buffer, int32_t current_line);
char *add_line(char *buffer, const char mode);
char *edit_line(char *buffer, int32_t current_line);
int32_t get_current_line(int32_t line_count);

int main(int argc, char **argv) {
    if(argc != 2) {
        printf("Usage: %s 'file_name'\n", argv[0]);
        return EXIT_FAILURE;
    }

    main_loop(argv[1]);
    return EXIT_SUCCESS;
}

void main_loop(char *filename) {
    char *buffer = file_read(filename);
    if(buffer == NULL) return;

    int32_t line_count = 0;
    int32_t current_line;

    str_print(buffer, &line_count);
    printf("Enter 'h' to see a list of commands or 'q' to quit\n");
    char opt;
    while(opt != 'q') {
        printf("> ");
        if((opt = getchar()) != '\n') clear_input_buffer();
        switch (opt) {
            case 'q':
                break;
            case 'h':
                print_help();
                break;
            case 'w':
                file_write(filename, buffer);
                break;
            case 'p':
                str_print(buffer, &line_count);
                break;
            case 'd':
                if(!(current_line = get_current_line(line_count))) continue;
                remove_line(buffer, current_line);
                line_count -= 1;
                break;
            case 'e':
                if(!(current_line = get_current_line(line_count))) continue;
                if(!(buffer = edit_line(buffer, current_line))) return;
                break;
            case 'n':
                line_count += 1;
                if(!(current_line = get_current_line(line_count))) continue;
                if(!(buffer = add_empty_line(buffer, current_line))) return;
                if(!(buffer = edit_line(buffer, current_line + 1))) return;
                break;
            case 'a':
                line_count += 1;
                buffer = add_line(buffer, 'a');
                break;
            case 'i':
                line_count += 1;
                buffer = add_line(buffer, 'i');
                break;
            default:
                printf("Invalid option!\n");
        }
    }
    free(buffer);
}

void print_help(void) {
    printf(
        "'p' -- print the contents of the buffer\n"
        "'d' -- delete a single line\n"
        "'e' -- edit a single line\n"
        "'a' -- append a single line to the end of the buffer\n"
        "'i' -- insert a single line to the start of the buffer\n"
        "'n' -- add a single line after the specified line number\n"
        "'h' -- print this list\n"
        "'q' -- quit\n"
    );
}

int32_t get_current_line(int32_t line_count) {
    printf("Enter line number: ");
    char *str = str_input(stdin);
    char *endptr;
    long current_line = strtol(str, &endptr, 0);
    if(*endptr != '\0') {
        printf("Invalid number\n");
        return 0;
    }
    if(current_line > line_count || current_line <= 0) {
        printf("Invalid line number\n");
        return 0;
    }
    return (int32_t)current_line;
}

void remove_line(char *buffer, int32_t current_line) {
    char *end = buffer;

    for(int i = 1; i < current_line; ++i) {
        end = strchr(end, '\n') + 1;
    }

    size_t len = end - buffer;
    end = strchr(end, '\n') + 1;
    memmove(buffer + len, end, strlen(end) + 1);
}

char *add_empty_line(char *buffer, int32_t current_line) {
    char *p_buffer = buffer;

    for(int i = 0; i < current_line; ++i) {
        p_buffer = strchr(p_buffer, '\n') + 1;
    }

    char *new_buffer = malloc(strlen(buffer) + 2);
    if(!new_buffer) {
        free(buffer);
        printf("add_empty_line: Malloc failed\n");
        return NULL;
    }

    sprintf(new_buffer, "%.*s\n%s",
        (int)(p_buffer - buffer),
        buffer,
        p_buffer
    );
    
    free(buffer);
    return new_buffer;
}

char *add_line(char *buffer, const char mode) {
    char *newline;
    char *new_buffer;

    switch(mode) {
        case 'a':
            newline = str_input(stdin);
            new_buffer = malloc(strlen(buffer) + strlen(newline) + 2);
            sprintf(new_buffer, "%s%s\n", buffer, newline);
            break;
        case 'i':
            newline = str_input(stdin);
            new_buffer = malloc(strlen(buffer) + strlen(newline) + 2);
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

char *edit_line(char *buffer, int32_t current_line) {
    char *buffer_start = strdup(buffer);
    char *buffer_end = buffer;

    for(int i = 1; i < current_line; ++i) {
        buffer_end = strchr(buffer_end, '\n') + 1;
    }

    buffer_start[buffer_end - buffer] = '\0';
    buffer_end = strchr(buffer_end, '\n');

    char *newline = str_input(stdin);
    if(!newline) {
        free(buffer);
        free(buffer_start);
        printf("edit_line: Newline is equal to NULL\n");
        return NULL;
    }

    char *new_buffer = malloc (
        strlen(buffer_start) + 
        strlen(newline) + 
        strlen(buffer_end) + 1
    );
    
    if(!new_buffer) {
        free(newline);
        free(buffer);
        free(buffer_start);
        printf("edit_line: Failed to malloc new buffer\n");
        return NULL;
    }

    sprintf(new_buffer, "%s%s%s",
        buffer_start,
        newline,
        buffer_end
    );

    free(newline);
    free(buffer);
    free(buffer_start);
    return new_buffer;
}
