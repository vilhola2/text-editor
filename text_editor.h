#include <stdint.h>
#include <stdio.h>

#ifndef TEXT_EDITOR_H
#define TEXT_EDITOR_H

void clear_input_buffer();

char *file_to_str(char *filename, size_t *size);
void file_write(char *filename, char *input);

void str_get(char *target, size_t *size);
void str_print(char *input, int32_t *line_count);
void str_reduce(char *input);

#endif
