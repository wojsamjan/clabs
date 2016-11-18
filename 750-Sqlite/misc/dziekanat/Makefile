#
#   $URL: http://manta.univ.gda.pl/svn/wb/labs/c/750-Sqlite/schema/Makefile $
#   $Revision: 151 $
#

schemas = products.sql produkty.sql

%.sqlite3 : %.sql
	sqlite3 $@ < $<

%.dump : %.sqlite3
	echo '.dump' | sqlite3 $<

%.archive : %.sqlite3
	echo '.dump' | sqlite3 $< > $@

dziekanat.sort : dziekanat.sqlite3
	@sqlite3 $< "select nazwisko, imię from student" | sort

clean :
	rm -f *~ *.sqlite3
