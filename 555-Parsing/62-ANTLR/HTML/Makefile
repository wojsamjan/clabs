
antlrloc = .:/usr/local/share/antlr-2.7.2/antlrall.jar

.PHONY : generate_java_files

all : Main.class

main = html.g

grammar_files = HTMLLexer.java HTMLParser.java HTMLTokenTypes.java

generate_java_files : $(main)
#	java -cp $(antlrloc) antlr.Tool t.g
	cantlr $(main)

Main.class : generate_java_files
	javac -classpath $(antlrloc) Main.java $(grammar_files)

clean :
	rm -f *~ \#* {HTMLLexer,HTMLParser,HTMLTokenTypes}.{java,class} \
 Main.class HTMLTokenTypes.txt

# uruchamiamy parser:
#
# export CLASSPATH=.:/usr/local/share/antlr-2.7.2/antlrall.jar
# java Main 
#   wlodek <Enter>     <- wpisujemy
#
# albo
#
# java -cp .:/usr/local/share/antlr-2.7.2/antlrall.jar Main
#   wlodek <Enter>
