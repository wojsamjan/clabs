
# WB, 11.XI.2003

ps = $(wildcard *.ps)
png = $(ps:.ps=.png)

.SUFFIXES : .png .ps

resolution = 50x50

#%.png : %.ps
#	gs -sDEVICE=pngalpha -sOutputFile=$@ -r$(resolution) -dEPSCrop -dBackgroundColor=16#ffffff -dTextAlphaBits=2 -dGraphicsAlphaBits=2 -q -dbatch -dNOPAUSE $< -c quit

%.bbox : %.ps
	gs -sDEVICE=bbox -sOutputFile=$@ -q -dbatch -dNOPAUSE $< -c quit


.PHONY : clean

clean :
	rm -f *~ \#* $(png)

%.png : %.ps
	gs -dBATCH -dNOPAUSE -q  -r$(resolution) \
-sDEVICE=ppm -dGraphicalAlphaBits=4 -sOutputFile=- $< \
| pnmcrop | pnmtopng -transparent =white > $@
	@identify $@
