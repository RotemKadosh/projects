CC=gcc
CFLAGS=-ansi -pedantic-errors -Wall -Wextra -g
DEPS = ../slist/slist.h queue.h 
OBJ = ../slist/slist.o queue.o queue_test.o 
.PHONY = run cgdb vlg clean ar

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
	ar rcs queue.ar $(OBJ) $(DEPS)

sl:
	ln -s ~/git/ds/queue/queue.h ~/git/ds/include

clean: 
	rm -f *.o *.out 

