csources = hanoi.c permutacje.c mondrian.c koch.c sierpinski.c hilbert.c
programs = $(csources:.c=)

all : $(programs)

mondrian : mondrian.c
	gccx $(CFLAGS) -o $@ $@.c
koch : koch.c
	gccx $(CFLAGS) -o $@ $@.c
sierpinski : sierpinski.c
	gccx $(CFLAGS) -o $@ $@.c
hilbert : hilbert.c
	gccx $(CFLAGS) -o $@ $@.c

.PHONY : clean

clean:
	rm -f core *.o *~ graphics.ps $(programs)
