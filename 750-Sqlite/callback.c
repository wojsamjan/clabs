#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

#include "util.h"

static int callback(void *NotUsed, int argc, char **argv, char **azColName);

int main() {
  sqlite3 *db;
  int rc;
  char *sql, *err;

  rc = sqlite3_open("jp.sqlite3", &db);
  if(rc) {
    print_error(db, "nie mogę otworzyć bazy");
    exit(1);
  }
  log_sql(db, 0);

  /*
  sql = "select studenci.nazwisko, studenci.imię, zaliczenia.ocena from studenci, zaliczenia"
        "  where studenci.id = zaliczenia.student_id"
        "  order by nazwisko, imię";
  */

  sql = "select nazwisko, imię from studenci"
        "  order by nazwisko, imię";

  rc = sqlite3_exec(db, sql, callback, NULL, &err);

  if (rc != SQLITE_OK) {
    if (err != NULL) {
      fprintf(stderr, "błąd sqlite3_exec(): %s\n", err);
      sqlite3_free(err);
    }
  }

  sqlite3_close(db);

  return 0;
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
  int i;
  for(i = 0; i < argc; i++){
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  printf("\n");
  return 0;
}
