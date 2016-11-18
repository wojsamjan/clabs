#
#  Makefile do przykladow omawianych na wykladzie
#  $URL:$
#  $Revision:$

CFLAGS = -g -Wall
LDFLAGS = -lm

csources = ship.c colors.c dtable.c czas.c \
clrscr.c dir.c popen.c uname.c pipe1.c pipe2.c keyboard.c yesterday.c

programs = $(csources:.c=)

% : %.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)
%.ps : %.c
	enscript -Xlatin2 -GE -p$@ $<


.PHONY: clean dist all.ps

# print which characters are missing, add fancy header, 2 columns, landscape

all.ps:
	enscript -Xlatin2 -2OGrE -p$@ $(programs)

clean:
	rm -f core *.o *~ *.ps $(programs)
