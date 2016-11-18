# $Revision: 1.6 $
# $Date: 2004/03/01 17:36:30 $

clean :
	rm -f *~ \#* a.out cplx hw *.o core pierw

pierw : main.o delta.o
	cc main.o delta.o -o pierw -lm

main.o : main.c delta.h
	cc -c main.c

delta.o : delta.c delta.h
	cc -c delta.c

cplx : cplx.c
	cc cplx.c -o cplx -lm
