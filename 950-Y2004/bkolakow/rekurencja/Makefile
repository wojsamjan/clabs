cc=gccx
cflags=-O2 -pedantic -Wall

main: binarycode graycode partitions subsets telefon clean

binarycode: binarycode.c
	$(cc) $(cflags) -o binarycode binarycode.c

graycode: graycode.c
	$(cc) $(cflags) -o graycode graycode.c

partitions: partitions.c
	$(cc) $(cflags) -o partitions partitions.c

subsets: subsets.c
	$(cc) $(cflags) -o subsets subsets.c

telefon: telefon.c
	$(cc) $(cflags) -o telefon telefon.c

.PHONY: clean

clean:
	rm -rf *~ 


