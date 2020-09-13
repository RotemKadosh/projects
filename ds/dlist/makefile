CC=gcc
CFLAGS=-ansi -pedantic-errors -Wall -Wextra -g
DEPS = dlist.h
OBJ = dlist.o dlist_test.o
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

ar: 
	ar rcs dlist.ar $(OBJ) $(DEPS)

sl:
	ln -s ~/git/ds/dlist/slist.h ~/git/ds/include

clean: 
	rm -f *.o *.out 
