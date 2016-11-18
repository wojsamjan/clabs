#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

#include "util.h"

int main() {
  sqlite3 *db;
  int rc;
  char *sql, *err;

  rc = sqlite3_open("jp.sqlite3", &db);
  if(rc) {
    print_error(db, "nie mogę otworzyć bazy");
    exit(1);
  }
  log_sql(db, 1);

  sql = "insert into studenci(nazwisko, imię, login, data) "
        "values('Aszybki', 'Zbig', 'zaszybki', datetime('now'))";

  rc = sqlite3_exec(db, sql, NULL, NULL, &err);

  if (rc != SQLITE_OK) {
    if (err != NULL) {
      fprintf(stderr, "błąd sqlite3_exec(): %s\n", err);
      sqlite3_free(err);
    }
  }

  sqlite3_close(db);  /* może zwrócić: SQLITE_BUSY */

  return 0;
}
