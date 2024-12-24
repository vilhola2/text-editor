CFLAGS=-g -pedantic-errors
CC=gcc

OBJ_DIR=obj/
OBJ=$(OBJ_DIR)*.o

OBJECTS=\
		text_editor.o \
		string.o \
		file.o \
		io.o \

all: text_editor

%.o: %.c
	$(CC) $(CFLAGS) -c -o $(OBJ_DIR)$@ $^

text_editor: $(OBJECTS)
	$(CC) $(CFLAGS) -o bin/$@ $(OBJ)

clean:
	rm $(OBJ)
