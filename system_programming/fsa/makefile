CC=gcc
CFLAGS=-ansi -pedantic-errors -Wall -Wextra -g
DEPS = fsa.h 
OBJ = fsa.o fsa_test.o 
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
	ln -s ~/git/system_programming/fsa/fsa.h ~/git/system_programming/include

clean: 
	rm -f *.o *.out *.gch
