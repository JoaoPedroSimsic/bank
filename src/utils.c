#include "utils.h"
#include <sqlite3.h>
#include <stdio.h>

int begin_transaction(sqlite3 *db) {
  char *err_msg = NULL;

  if (sqlite3_exec(db, "BEGIN TRANSACTION;", NULL, NULL, &err_msg) !=
      SQLITE_OK) {
    fprintf(stderr, "BEGIN failed: %s\n", err_msg);
    sqlite3_free(err_msg);

    return -1;
  }

  return 0;
}

int commit_transaction(sqlite3 *db) {
  char *err_msg = NULL;

  if (sqlite3_exec(db, "COMMIT", NULL, NULL, &err_msg) != SQLITE_OK) {
    fprintf(stderr, "COMMIT failed: %s\n", err_msg);
    sqlite3_free(err_msg);

    return -1;
  }

  return 0;
}

int rollback_transaction(sqlite3 *db) {
  char *err_msg = NULL;

  if (sqlite3_exec(db, "ROLLBACK", NULL, NULL, &err_msg) != SQLITE_OK) {
    fprintf(stderr, "ROLLBACK failed: %s\n", err_msg);
    sqlite3_free(err_msg);

    return -1;
  }

  return 0;
}

int exec_sql(sqlite3 *db, const char *sql) {
	char *err_msg = NULL;

	if (sqlite3_exec(db, sql, NULL, NULL, &err_msg) != SQLITE_OK) {
		fprintf(stderr, "SQL execution failed: %s\nQuery: %s\n", err_msg, sql);
		rollback_transaction(db);
		sqlite3_free(err_msg);

		return -1;
	}

	return 0;
}
