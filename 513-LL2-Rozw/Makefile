#   Plik:  Makefile do zadañ z list powi±zanych
# Wersja:  31 X 2002
#  Autor:  W. Bzyl, <matwb@univ.gda.pl>

archive = 06-LinkedLists-Cont-Solutions.tar.gz

CFLAGS = -Wall -ggdb

exercises = FrontBackSplit.c RemoveDuplicates.c \
MoveNode.c AlternatingSplit.c ShuffleMerge.c SortedMerge.c MergeSort.c \
SortedIntersect.c Reverse.c

programs = $(exercises:%.c=%)
object_files = $(exercises:%.c=%.o)

sources = Makefile utils.c utils.h $(exercises)

%.o : %.c utils.h

FrontBackSplit : FrontBackSplit.o utils.o
	$(CC) $^ -o $@
RemoveDuplicates : RemoveDuplicates.o utils.o
	$(CC) $^ -o $@
MoveNode : MoveNode.o utils.o
	$(CC) $^ -o $@
AlternatingSplit : AlternatingSplit.o utils.o
	$(CC) $^ -o $@
ShuffleMerge : ShuffleMerge.o utils.o
	$(CC) $^ -o $@
SortedMerge : SortedMerge.o utils.o
	$(CC) $^ -o $@
MergeSort : MergeSort.o utils.o
	$(CC) $^ -o $@
Reverse : Reverse.o utils.o
	$(CC) $^ -o $@

.PHONY : clean dist

clean :
	rm -f *~ \#* core $(object_files) $(programs) programs.{ps,ljet4} \
utils.o

dist :
	tar zcvf $(archive) $(sources)

programs.ps: $(exercises)
	enscript -GE -p$@ $^
#	enscript -Xlatin2 -G2rE -U2 -p$@ $< 

programs.ljet4 : programs.ps
	gs -dNOPAUSE -dBATCH -sDEVICE=ljet4 -sOutputFile=programs.ljet4 $<
