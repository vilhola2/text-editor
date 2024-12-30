#include "text_editor.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void main_loop(char *filename);
void print_help(void);

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
                if(!(buffer = edit_line(buffer, current_line, true))) return;
                break;
            case 'n':
                line_count += 1;
                if(!(current_line = get_current_line(line_count))) continue;
                if(!(buffer = edit_line(buffer, current_line, false))) return;
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
        "'n' -- add a single line at the specified line number\n"
        "'h' -- print this list\n"
        "'q' -- quit\n"
    );
}
