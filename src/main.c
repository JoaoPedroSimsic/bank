#include "db.h"
#include "transactions.h"
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>

#define CLEAR_SCREEN "\033[2J\033[H"
#define COLOR_GREEN  "\x1b[32m"
#define COLOR_RED    "\x1b[31m"
#define COLOR_RESET  "\x1b[0m"

void print_balances(sqlite3 *db) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT id, user_id, balance FROM accounts;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Error reading accounts.\n");
        return;
    }

    printf("\n--- Account Balances ---\n");
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        int user_id = sqlite3_column_int(stmt, 1);
        double balance = sqlite3_column_double(stmt, 2);
        printf("ID: %d | User: %d | Balance: $%.2f\n", id, user_id, balance);
    }
    printf("------------------------\n");

    sqlite3_finalize(stmt);
}

void display_menu() {
    printf("\n--- Banking TUI (Testing User 101) ---\n");
    printf("1: Deposit $100 to Account 1\n");
    printf("2: Withdraw $50 from Account 2\n");
    printf("3: Transfer $200 from Acc 1 to Acc 2 (Success)\n");
    printf("4: Transfer $5000 from Acc 1 to Acc 3 (Fail: Insufficient Funds)\n");
    printf("R: Reset/Re-initialize Database\n");
    printf("Q: Quit\n");
    printf("Enter choice: ");
}

int main(void) {
    sqlite3 *db = NULL;
    int rc = init_db("bank.db", &db);

    if (rc != 0) {
        close_db(db);
        return 1;
    }

    setup_db(db);

    char choice;
    int transaction_status;
    const char *result_message;
    const char *color_code;

    while (1) {
        printf(CLEAR_SCREEN);

        print_balances(db);
        display_menu();

        if (scanf(" %c", &choice) != 1) {
            while (getchar() != '\n')
                ;
            continue;
        }

        while (getchar() != '\n'); 

        switch (choice) {
        case '1':
            fprintf(stderr, "\n-> Executing Deposit $100 to Account 1...\n");
            transaction_status = deposit(db, 1, 100.00);
            break;
        case '2':
            fprintf(stderr, "\n-> Executing Withdraw $50 from Account 2...\n");
            transaction_status = withdraw(db, 2, 50.00);
            break;
        case '3':
            fprintf(stderr, "\n-> Executing Transfer $200 from Acc 1 to Acc 2...\n");
            transaction_status = transfer(db, 101, 1, 2, 200.00);
            break;
        case '4':
            fprintf(stderr, "\n-> Executing Transfer $5000 from Acc 1 to Acc 3 (EXPECTING FAILURE)...\n");
            transaction_status = transfer(db, 101, 1, 3, 5000.00);
            break;
        case 'R':
        case 'r':
            setup_db(db);
            continue; 
        case 'Q':
        case 'q':
            goto cleanup;
        default:
            fprintf(stderr, "\n%sInvalid choice. Try again.%s\n", COLOR_RED, COLOR_RESET);
            printf("\nPress Enter to Continue...");
            getchar();
            continue;
        }

        if (transaction_status == 0) {
            result_message = "SUCCESS";
            color_code = COLOR_GREEN;
        } else if (transaction_status == 1) {
            result_message = "FAILURE (Insufficient Funds)";
            color_code = COLOR_RED;
        } else {
            result_message = "FAILURE (Error)";
            color_code = COLOR_RED;
        }

        fprintf(stderr, "Result: %s%s%s\n", color_code, result_message, COLOR_RESET);

        printf("\nPress Enter to Continue...");
        getchar();
    }

cleanup:
    close_db(db);
    printf("\nExiting TUI.\n");
    return 0;
}
