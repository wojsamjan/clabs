#
# JP2                             14.XII.2003
#
#

CFLAGS = -Wall -g

csources = main.c 

all : kosinus kosinus2 loader

module1.so : module1.c
	$(CC) -fPIC module1.c -c
	$(CC) -shared module1.o -o module1.so

module2.so : module2.c
	$(CC) -fPIC module2.c -c
	$(CC) -shared module2.o -o module2.so

loader : main.o module1.so module2.so
	$(CC) main.o -ldl -o loader
#       ./loader module1.so
#       ./loader module2.so

kosinus : kosinus.o 
	$(CC) -rdynamic $^ -ldl -o $@

kosinus2 : kosinus2.o 
	$(CC) -rdynamic $^ -ldl -o $@

.PHONY : clean 

clean:
	rm -f core \#* *~ *.{o,so} *.ps loader kosinus kosinus2

