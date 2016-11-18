CC = c99
CFLAGS = -g -Wall
LDLIBS = -lm

# % : %.c
#	$(CC) $(CFLAGS) -o $@ $< $(LDLIBS)

csources =  deszcz.c tab-wsk.c sadstrings.c getstrings.c

programs = $(csources:.c=)

.PHONY : clean

clean :
	rm -f a.out *.o *~ $(programs)
