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

int setup_db(sqlite3 *db) {
    char *err_msg = NULL;
    const char *sql = 
        "DROP TABLE IF EXISTS accounts;"
        "DROP TABLE IF EXISTS transactions;"
        
        "CREATE TABLE accounts("
        "id INTEGER PRIMARY KEY, "
        "user_id INTEGER NOT NULL, " 
        "balance REAL NOT NULL DEFAULT 0);"
        
        "CREATE TABLE transactions("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "type TEXT NOT NULL DEFAULT 'transfer', "
        "from_account INTEGER, "
        "to_account INTEGER, "
        "amount REAL NOT NULL CHECK(amount > 0), "
        "timestamp DATETIME DEFAULT CURRENT_TIMESTAMP, "
        "FOREIGN KEY(from_account) REFERENCES accounts(id), "
        "FOREIGN KEY(to_account) REFERENCES accounts(id), "
        "CHECK(from_account IS NOT NULL OR to_account IS NOT NULL)"
        ");"
        
        "INSERT INTO accounts (id, user_id, balance) VALUES (1, 101, 1000.00);"
        "INSERT INTO accounts (id, user_id, balance) VALUES (2, 101, 500.00);"
        "INSERT INTO accounts (id, user_id, balance) VALUES (3, 102, 200.00);";

    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "DB Setup failed: %s\n", err_msg);
        sqlite3_free(err_msg);
        return -1;
    }
    printf("Database initialized with accounts.\n");
    return 0;
}

void close_db(sqlite3 *db) { sqlite3_close(db); }
