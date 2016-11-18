#
# Brian W. Kernighan, Denis M. Ritchie
# Język ANSI C 
# 8.6  Przykład -- wypisywanie wartosci skorowidzów
#
# Skorowidz jest plikiem. Pozycja w skorowidzu składa się 
# z dwóch obiektów: numeru węzła (ang. inode number) i nazwy pliku


CC = gcc
CFLAGS = -Wall -g

csources = main.c fsize.c 

programs = $(csources:.c=)


fsize : main.o fsize.o

fsize.o : fsize.c fsize.h

main.o : main.c fsize.h


# zob. http://www.gnu.org/software/make/manual/make.html#Pattern-Rules

%.ps : %.c
	iconv -f utf8 -t latin2 $< | a2ps -X iso2 -o $@


.PHONY : clean 

all : $(programs)

clean:
	rm -f core \#* *~ *.o *.ps $(programs)
