#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int id;
  char name[50];
  float balance;
} Account;

extern Account *clients;
extern int client_count;
extern int max_clients;

void initialize_clients_array(int initial_size);
void add_new_client(int id, const char *name);
void list_all_clients();
Account *find_client_by_id(int id);

#endif
