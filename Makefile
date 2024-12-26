CFLAGS=-g -pedantic-errors
CC=gcc

OBJ_DIR=obj/
OBJ=$(OBJ_DIR)*.o
BIN=text_editor
BIN_DIR=bin/

OBJECTS=\
		main.o \
		file.o \
		io.o \
		string.o \

all: text_editor

%.o: %.c
	$(CC) $(CFLAGS) -c -o $(OBJ_DIR)$@ $^

text_editor: $(OBJECTS)
	$(CC) $(CFLAGS) -o $(BIN_DIR)$(BIN) $(OBJ)

clean:
	rm $(OBJ)

clean_bin: clean
	rm $(BIN_DIR)$(BIN)
