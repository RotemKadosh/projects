CC=gcc
CFLAGS=-ansi -pedantic-errors -Wall -Wextra -g -lm
DEPS = calc.h parser.h stack.h 
OBJ = calc.c calc_test.c ../parser/parser.c ../../stack/stack.c 
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
	ar rcs calculator.ar $(OBJ) $(DEPS)

clean: 
	rm -f *.o *.out *.gch
