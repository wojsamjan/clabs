
antlrloc = .:/usr/local/share/antlr-2.7.2/antlrall.jar

all : Main.class

P.java : t.g
	java -cp $(antlrloc) antlr.Tool t.g

Main.class : Main.java P.java
	javac -classpath $(antlrloc) *.java

clean :
	rm -f *~ \#* {L,P,PTokenTypes}.{java,class} Main.class PTokenTypes.txt

# uruchamiamy parser:
#
# export CLASSPATH=.:/usr/local/share/antlr-2.7.2/antlrall.jar
# java Main < input
#
# albo
#
# java -cp .:/usr/local/share/antlr-2.7.2/antlrall.jar Main < input
