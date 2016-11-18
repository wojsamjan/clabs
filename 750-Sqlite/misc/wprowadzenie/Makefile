

all : foods.db chapter4.db


foods.db : foods.sql
	sqlite3 $@ < $^

chapter4.db : chapter4.sql
	sqlite3 $@ < $^

clean :
	rm -f *~ \#* foods.db chapter4.db
