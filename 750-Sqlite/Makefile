
CFLAGS = -Wall -ansi
LDFLAGS = -lsqlite3

clean :
	rm -f *~ \#* *~ *.o hello-sqlite-capi *.sqlite3 exec callback

exec : exec.c util.o

callback : callback.c util.o

util.o : util.c util.h

jp baza jp.sqlite3 : jp.sql grupa1.sql zaliczenia1.sql
	sqlite3 jp.sqlite3 < jp.sql
	sqlite3 jp.sqlite3 < grupa1.sql
	sqlite3 jp.sqlite3 < zaliczenia1.sql

hello-sqlite-capi : hello-sqlite-capi.c




