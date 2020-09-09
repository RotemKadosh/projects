CC=gcc
CFLAGS=-ansi -pedantic-errors -Wall -Wextra -g
DEPS = circular_buffer.h 
OBJ = circular_buffer.o circular_buffer_test.o 
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
	ar rcs circular_buffer.ar $(OBJ) $(DEPS)

sl:
	ln -s ~/git/ds/circular_buffer/circular_buffer.h ~/git/ds/include

clean: 
	rm -f *.o *.out 

