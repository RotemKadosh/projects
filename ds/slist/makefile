CC=gcc
CFLAGS=-ansi -pedantic-errors -Wall -Wextra -g
DEPS = slist.h
OBJ = slist.o slist_test.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) 
						
a.out: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)  


