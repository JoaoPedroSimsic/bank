#include "db.h"
#include <sqlite3.h>
#include <stdio.h>

int init_db(const char *db_file, sqlite3 **db) {
  int rc = sqlite3_open(db_file, db);

  if (rc) {
    fprintf(stderr, "Cannot open DB: %s\n", sqlite3_errmsg(*db));
    return rc;
  }

  return 0;
}

void close_db(sqlite3 *db) { sqlite3_close(db); }
