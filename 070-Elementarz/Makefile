programs = zs zz remove_comments remove_comments2 remove_comments3 vararg

CFLAGS = -std=c11 -Wall
CPPFLAGS = -Wno-unused-function

zs : zs.o
	$(CC) -o $@ $<
zz : zz.o
	$(CC) -o $@ $<

.PHONE: clean

clean:
	rm -f core *.o *~ *.ps $(programs) fcopy test-day
