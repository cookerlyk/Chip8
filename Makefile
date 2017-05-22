# Which compiler will be used.
CC=gcc

# CFLAGS specifies compiler options
CFLAGS=-c -std=c99 -Wall -Wextra

# Compiler and linker options for SDL2
SDL_CFLAGS= $(shell sdl2-config --cflags)
SDL_LFLAGS= $(shell sdl2-config --libs)

override CFLAGS += $(SDL_CFLAGS)

# Directory paths for the Header files and the Source files
HEADERDIR= src/
SOURCEDIR= src/

HEADER_FILES= instructions.h chip8.h screen.h chip8_t.h
SOURCE_FILES= main.c chip8.c screen.c instructions.c

# Add the file path (FP) to the Header and Source files
HEADERS_FP = $(addprefix $(HEADERDIR),$(HEADER_FILES))
SOURCE_FP = $(addprefix $(SOURCEDIR),$(SOURCE_FILES))

# Create the object files
OBJECTS =$(SOURCE_FP:.c = .o)

# Program to build
EXECUTABLE=chip8

# --------------------------------------------

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(SDL_LFLAGS) -o $(EXECUTABLE)

%.o: %.c $(HEADERS_FP)
	$(CC) $(CFLAGS) -o $@ $< 

clean:
	rm -rf src/*.o $(EXECUTABLE)