CC=gcc
CFLAGS=-ansi -pedantic-errors -Wall -Wextra -g
DEPS = pqueue.h dlist.h sorted_list.h
OBJ = pqueue.o pqueue_test.o ../dlist/dlist.o ../sorted_list/sorted_list.o ../dlist/dlist.h ../sorted_list/sorted_list.h
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

gc:
	gcc -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 $(OBJ) $(DEPS) 

ar: 
	ar rcs pqueue.ar $(OBJ) $(DEPS)

sl:
	ln -s ~/git/ds/pqueue/pqueue.h ~/git/ds/include

clean: 
	rm -f *.o *.out *.gch
