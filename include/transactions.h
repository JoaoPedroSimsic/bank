#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include <sqlite3.h>

int deposit (sqlite3 *db, int account_id, double amount);
int withdraw(sqlite3 *db, int account_id, double amount);
int transfer (sqlite3 *db, int user_id, int from_id, int to_id, double amount);

#endif 
