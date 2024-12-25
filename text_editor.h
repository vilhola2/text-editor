#include <stdint.h>
#include <stdio.h>

#ifndef TEXT_EDITOR_H
#define TEXT_EDITOR_H

#define ERR 1
#define NOERR 0

void clear_input_buffer(void);

char *file_read(char *filename);
void file_write(char *filename, char *input);

int32_t str_get_line_count(char *buffer);
char *str_input(void);
void str_print(char *input, int32_t *line_count);
void str_reduce(char *input);

#endif
