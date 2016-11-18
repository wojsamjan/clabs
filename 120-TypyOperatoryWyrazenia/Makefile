# (WB)                                 31 marca 2003

CFLAGS = -g -pedantic -ansi -Wall

sources = conv.c strl.c test-day1.c test-day2.c enum.c squeeze.c bit.c \
 widget
programs = $(sources:%.c=%)

widget : widget.c
	$(CC) -ggdb $^ -o $@

.PHONY: clean

clean:
	rm -f core *.o *~ \#* $(programs)
