#include "transactions.h"
#include "utils.h"
#include <sqlite3.h>
#include <stdio.h>

int deposit(sqlite3 *db, int account_id, double amount) {
    if (amount <= 0)
        return -1;

    char sql[256];

    if (begin_transaction(db) != 0)
        return -1;

    snprintf(sql, sizeof(sql),
             "UPDATE accounts SET balance = balance + %.2f WHERE id = %d;",
             amount, account_id);

    if (exec_sql(db, sql) != 0) {
        rollback_transaction(db);
        return -1;
    }

    snprintf(sql, sizeof(sql),
             "INSERT INTO transactions (type, to_account, amount) VALUES "
             "('deposit', %d, %.2f);",
             account_id, amount);

    if (exec_sql(db, sql) != 0) {
        rollback_transaction(db);
        return -1;
    }

    commit_transaction(db);

    return 0;
}

int withdraw(sqlite3 *db, int account_id, double amount) {
    if (amount <= 0)
        return -1;

    char sql[256];
    sqlite3_stmt *stmt;
    double balance = 0.0;

    snprintf(sql, sizeof(sql), "SELECT balance FROM accounts WHERE id = %d;",
             account_id);

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK)
        return -1;

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        balance = sqlite3_column_double(stmt, 0);
    }
    sqlite3_finalize(stmt);

    if (balance < amount) {
        fprintf(stderr, "Insufficient funds\n");
        return 1;
    }

    if (begin_transaction(db) != 0)
        return -1;

    snprintf(sql, sizeof(sql),
             "UPDATE accounts SET balance = balance - %.2f WHERE id = %d;",
             amount, account_id);

    if (exec_sql(db, sql) != 0) {
        rollback_transaction(db);
        return -1;
    }

    snprintf(sql, sizeof(sql),
             "INSERT INTO transactions (type, from_account, amount) VALUES "
             "('withdraw', %d, %.2f);",
             account_id, amount);

    if (exec_sql(db, sql) != 0) {
        rollback_transaction(db);
        return -1;
    }

    commit_transaction(db);

    return 0;
}

int transfer(sqlite3 *db, int user_id, int from_id, int to_id, double amount) {
	if (amount <= 0 || from_id == to_id) {
        fprintf(stderr, "Invalid transfer parameters.\n");
        return -1;
    }

    char sql[256];
    sqlite3_stmt *stmt;
    double balance = 0.0;

    snprintf(sql, sizeof(sql), "SELECT balance FROM accounts WHERE id = %d;",
             from_id);

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK)
        return -1;

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        balance = sqlite3_column_double(stmt, 0);
    }
    sqlite3_finalize(stmt);

    if (balance < amount) {
        fprintf(stderr, "Insufficient funds\n");
        return 1; 
    }
    
    if (begin_transaction(db) != 0)
        return -1;

    snprintf(sql, sizeof(sql),
             "UPDATE accounts SET balance = balance - %.2f WHERE id = %d;",
             amount, from_id);

    if (exec_sql(db, sql) != 0) {
        return -1;
    }

    snprintf(sql, sizeof(sql),
             "UPDATE accounts SET balance = balance + %.2f WHERE id = %d;",
             amount, to_id);

    if (exec_sql(db, sql) != 0) {
        return -1;
    }

    snprintf(sql, sizeof(sql),
             "INSERT INTO transactions (type, from_account, to_account, amount) "
             "VALUES ('transfer', %d, %d, %.2f);",
             from_id, to_id, amount);

    if (exec_sql(db, sql) != 0) {
        return -1;
    }

    commit_transaction(db);

    return 0;
}
