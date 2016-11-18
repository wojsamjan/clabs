# ------------------------------------------------------------------------
# $Source: /var/cvs/wyklady/JP1-L/80-ProgramowanieOpisowe/Makefile,v $
# $Date: 2004/11/22 11:13:16 $
# $Revision: 1.3 $
# ------------------------------------------------------------------------
# This Makefile belongs to the CWEB-NLS package.
# ------------------------------------------------------------------------

language = pl_PL

literate_sources = hello.w hello2.w fw.w fw2.w sample.w

programs = $(literate_sources:.w=) 
tex_programs = $(literate_sources:.w=.tex) 

CWEAVE-NLS=cw
CTANGLE-NLS=ct

CFLAGS=-g -Wall

.SUFFIXES: 
.SUFFIXES: .tex .dvi .pdf .ps .w .c .o

%.tex : %.w
	LANG=$(language) $(CWEAVE-NLS) $<

%.dvi : %.tex
	mex -translate-file=il2-pl "\let\pdf+ \input $*"

%.pdf: %.dvi
	dvipdfm $*.dvi

%.ps : %.pdf
	pdf2ps $<

%.c : %.w
	LANG=$(language) $(CTANGLE-NLS) $<

clean:
	-rm -f *.log *.toc *.scn *.idx *.dvi *.pdf *.ps *.ljet4 \
*.h *.c *.o *~ \#* $(tex_programs) $(programs) witaj.{c,h}
