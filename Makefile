  CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=build/%.o)

LIB = libdata_structures.a

all: $(LIB) main

# Ensure build directory exists
build:
	mkdir -p build

# Compile .c -> build/.o
build/%.o: src/%.c | build
	$(CC) $(CFLAGS) -c $< -o $@

# Build static library
$(LIB): $(OBJ)
	ar rcs $(LIB) $(OBJ)

clean:
	rm -rf build *.a