#ifndef DB_H
#define DB_H

#include <sqlite3.h>

int init_db(const char *db_file, sqlite3 **db);
int setup_db(sqlite3 *db);
void close_db(sqlite3 *db);

#endif 
