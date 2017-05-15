# Which compiler will be used.
CC=gcc

# CFLAGS specifies compiler options

CFLAGS=-c -std=c99 -Wall -Wextra -Iinc

# All of the .h header files to use as dependencies
HEADERS= src/instructions.h src/chip8.h

# All of the object files to produce as intermediary work
OBJECTS= src/main.o src/chip8.o src/instructions.o

SOURCEDIR = src/

# The final program to build
EXECUTABLE=chip8

# --------------------------------------------

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -rf src/*.o $(EXECUTABLE)