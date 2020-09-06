CC=gcc
CFLAGS=-ansi -pedantic-errors -Wall -Wextra -g
DEPS = ../slist/slist.h queue.h 
OBJ = ../slist/slist.o queue.o queue_test.o 
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
	ar rcs queue.ar $(OBJ) $(DEPS)

clean: 
	rm -f *.o *.out 

