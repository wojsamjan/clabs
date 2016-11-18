
all : markov

clean :
	rm -f *~ a.out *.o markov

markov.o : markov.c eprintf.h

eprintf.o : eprintf.c eprintf.h

markov : markov.o eprintf.o
	cc -Wall -ansi -g $^ -o $@

show : markov
	cat so.txt | markov | fmt | more
