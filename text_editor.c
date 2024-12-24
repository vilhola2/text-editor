#include "text_editor.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main_loop(char *filename);
void print_help();
void edit_line(char *buffer, int32_t current_line, size_t *size);
int32_t get_current_line(int32_t line_num);

int main(int argc, char **argv) {
    if(argc != 2) {
        printf("Usage: %s 'file_name'\n", argv[0]);
        return EXIT_FAILURE;
    }
    main_loop(argv[1]);
    return EXIT_SUCCESS;
}

void main_loop(char *filename) {
    size_t size;
    char *buffer = file_read(filename, &size);
    if(buffer == NULL) {
        printf("Error reading file!\n");
        return;
    }

    int32_t line_count = 0;
    int32_t current_line;

    str_print(buffer, &line_count);
    printf("Enter 'h' to see a list of commands or 'q' to quit\n");
    char opt;
    while(opt != 'q') {
        printf("> ");
        scanf(" %c", &opt);
        clear_input_buffer();
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
            case 'e':
                current_line = get_current_line(line_count);
                edit_line(buffer, current_line, &size);
                line_count = str_get_line_count(buffer);
                break;
            default:
                printf("Invalid option! Try again:\n");
        }
    }
    free(buffer);
}

void print_help() {
    printf( "'p' -- print the contents of the buffer\n"
            "'e' -- edit a single line\n"
            // todo "'a' -- append a single line to the end of the buffer"
            "'h' -- print this list\n"
            "'q' -- quit\n");
}

void edit_line(char *buffer, int32_t current_line, size_t *size) {
    *size *= 2;
    for(int i = 1; i < current_line; ++i) {
        buffer = strchr(buffer, '\n') + 1;
    }
    char *line_end = strchr(buffer, '\n');
    str_input(buffer, size);
    strcpy(buffer + strlen(buffer), line_end);
}

int32_t get_current_line(int32_t line_count) {
    int current_line;
    printf("Enter line number: ");
    while(1) {
        if(!scanf("%d", &current_line)) {
            printf("Invalid line number!\n");
            printf("Try again: ");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();
        if(current_line < 1 || current_line > line_count) {
            printf("Error: Non-existent line!\n");
            printf("Try again: ");
            continue;
        }
        break;
    }
    return current_line;
}
