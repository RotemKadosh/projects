CC=gcc
CFLAGS=-ansi -pedantic-errors -Wall -Wextra -g
DEPS = scheduler.h task.h pqueue.h uid.h
OBJ = scheduler.o scheduler_test.o ../task/task.o ../uid/uid.o ../pqueue/pqueue.o ../sorted_list/sorted_list.o ../dlist/dlist.o
.PHONY = run cgdb vlg clean ar sl gc

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
	ar rcs sorted_list.ar $(OBJ) $(DEPS)

sl:
	ln -s ~/git/ds/scheduler/scheduler.h ~/git/ds/include

clean: 
	rm -f *.o *.out *.gch
