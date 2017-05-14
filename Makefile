# CC specifies which compiler will be used.
CC=gcc

# CFLAGS specifies compiler options

CFLAGS=-c -std=c99 -Wall -Wextra

# All of the .h header files to use as dependencies
HEADERS=

# All of the object files to produce as intermediary work
OBJECTS=main.o

# The final program to build
EXECUTABLE=chip8

# --------------------------------------------

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -rf *.o $(EXECUTABLE)