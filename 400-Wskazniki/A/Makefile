#
#                                       1.X.2003
# Makefile do przykladow omawianych na wykladzie

CFLAGS = -Wall -g

# Najpierw omówić locales na przykładzie `tl.c'
# Następnie `man qsort'

csources = tl.c nsort.c ssort.c psort.c n.c ss.c ps.c
programs = $(csources:.c=)
data = text1.txt text2.txt text3.txt

.PHONY : clean

clean :
	rm -f *~ \#* core *.o $(programs)
