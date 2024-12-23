CFLAGS=-g -pedantic-errors
CC=gcc

OBJ_DIR=obj/
OBJ=$(OBJ_DIR)*.o

OBJECTS=\
		text_editor.o \
		str_functions.o \
		file_functions.o \
		input_functions.o \

all: text_editor

%.o: %.c
	$(CC) $(CFLAGS) -c -o $(OBJ_DIR)$@ $^

text_editor: $(OBJECTS)
	$(CC) $(CFLAGS) -o obj/$@ $(OBJ)

clean:
	rm $(OBJ)
