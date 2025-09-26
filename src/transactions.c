#include "transactions.h"
#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>

int deposit(sqlite3 *db, int account_id, double amount) {
	if (amount <= 0) return -1;

	char *err_msg = NULL;
	char sql[256];


}
