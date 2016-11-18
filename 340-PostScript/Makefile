#
# $Date: 2004/11/29 20:25:40 $
# $Revision: 1.3 $

ps = $(wildcard *.ps)
png = $(ps:.ps=.png)

.SUFFIXES : .png .ps

resolution = 50x50

%.png : %.ps
	gs -dBATCH -dNOPAUSE -q  -r$(resolution) \
-sDEVICE=ppm -dGraphicalAlphaBits=4 -sOutputFile=- $< \
| pnmcrop | pnmtopng -transparent =white > $@
	@identify $@

%.bbox : %.ps
	gs -sDEVICE=bbox -sOutputFile=$@ -q -dbatch -dNOPAUSE $< -c quit

.PHONY : clean

clean :
	rm -f *~ \#* $(png) programs.ps

programs.ps : $(sources)
	enscript -GE -U2 -p$@ $^
