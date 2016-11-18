
CC = cc 

target: cdemo

cdemo: cdemo.o plik1.o plik2.o
	$(CC) cdemo.o plik1.o plik2.o -o cdemo
cdemo.o: cdemo.c cdemo.h
	$(CC) -c cdemo.c -o cdemo.o
plik1.o: plik1.c cdemo.h
	$(CC) -c plik1.c -o plik1.o
plik2.o: plik2.c cdemo.h
	$(CC) -c plik2.c -o plik2.o

clean:
	rm -f *.o cdemo *~
