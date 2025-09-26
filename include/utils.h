#ifndef UTILS_H
#define UTILS_H

#include <sqlite3.h>

int begin_transaction(sqlite3 *db);
int commit_transaction(sqlite3 *db);
int rollback_transaction(sqlite3 *db);

int exec_sql(sqlite3 *db, const char *sql);

#endif 
