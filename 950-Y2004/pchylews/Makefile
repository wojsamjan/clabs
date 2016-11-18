
all : teq

clean :
	rm -f *~ *.o teq

teq : teq.o screen.o
	gcc -o $@ $^ -lncurses

%.o : %.c
	gcc -o $@ -c -Wall -g $^

dist : clean
	tar jcvf teq.tar.bz2 *.c *.h Makefile
