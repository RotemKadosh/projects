CC=gcc
CFLAGS=-ansi -pedantic-errors -Wall -Wextra -g
DEPS = vector.h
OBJ = vector.o vector_test.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) 
						
vector_all: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)  

vector_lib_ar: $(OBJ)
	ar rcs libfoo.ar $(OBJ)
