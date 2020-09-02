CC=gcc
CFLAGS=-ansi -pedantic-errors -Wall -Wextra -g
DEPS = slist.h
OBJ = slist.o slist_test.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) 
						
slist.out: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)  

vector_lib_ar: $(OBJ)
	ar rcs libfoo.ar $(OBJ)
