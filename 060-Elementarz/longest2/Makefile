CC = clang
CFLAGS = -Wall -std=c11

clean :
	rm -f *~ a.out longest \
 longest2 test-getline {main,copy,getline,test-getline}.o main2.o \
 tz tz.{log,dvi,ps,pdf,c,tex,idx,scn,toc}

longest : longest.c
	$(CC) $(CFLAGS) -o $@ $<

longest2 : main2.o copy.o getline.o
	$(CC) $(CFLAGS) -o $@ $^

main2.o : main2.c copy.h getline.h
	$(CC) -c $(CFLAGS) -o $@ $<

copy.o : copy.c copy.h
	$(CC) -c $(CFLAGS) -o $@ $<

getline.o : getline.c getline.h
	$(CC) -c $(CFLAGS) -o $@ $<

test-getline.o : test-getline.c
	$(CC) -c $(CFLAGS) -o $@ $<

test-getline : test-getline.o getline.o
	$(CC) $(CFLAGS) -o $@ $^


tz : tz.w
	ct tz.w
	cc -o tz tz.c

.SUFFIXES :
.SUFFIXES : .w .tex .dvi .pdf .ps

%.tex : %.w
	LANG=pl_PL cw $<

%.dvi : %.tex
	mex -translate-file=il2-pl "\let\pdf+ \input $*"

%.pdf: %.dvi
	dvipdfm $*.dvi

%.ps : %.pdf
	pdf2ps $<
