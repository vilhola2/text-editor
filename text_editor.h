#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#ifndef TEXT_EDITOR_H
#define TEXT_EDITOR_H

void clear_input_buffer(void);

char *file_read(char *filename);
void file_write(char *filename, char *input);

char *str_input(FILE *stream);
int32_t str_get_line_count(char *input);
void str_print(char *input, int32_t *line_count);

void remove_line(char *buffer, int32_t current_line);
char *add_line(char *buffer, const char mode);
char *edit_line(char *buffer, int32_t current_line, const bool replace_line);
int32_t get_current_line(int32_t line_count);

#endif
