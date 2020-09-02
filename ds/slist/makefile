CC=gcc
CFLAGS=-ansi -pedantic-errors -Wall -Wextra -g
DEPS = slist.h
OBJ = slist.o slist_test.o
.PHONY = run cgdb vlg clean

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) 
						
a.out: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)  

run: a.out
	./a.out

cgdb: a.out
	cgdb a.out

vlg: a.out
	   valgrind --leak-check=yes --track-origins=yes ./a.out

clean: 
	rm -f *.o *.out

