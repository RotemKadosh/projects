CC=gcc
CFLAGS=-ansi -pedantic-errors -Wall -Wextra -g
DEPS = stack.h
OBJ = stack.o stack_test.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) 
						
stack_all: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)  

libfoo.ar: $(OBJ)
	ar rcs libfoo.ar $(OBJ)
