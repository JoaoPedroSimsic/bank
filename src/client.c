#include "client.h"
#include <stdio.h>
#include <string.h>

Account *clients = NULL;
int client_count = 0;
int max_clients = 0;

void initialize_clients_array(int initial_size) {
  clients = (Account *)malloc(initial_size * sizeof(Account));
  if (clients == NULL) {
    printf("Error allocating memory for clients.\n");
    exit(1);
  }

  max_clients = initial_size;
}

void add_new_client(int id, const char *name) {
  if (client_count >= max_clients) {
    printf("Error: Client limit reached.\n");
    return;
  }

  clients[client_count].id = id;
  strcpy(clients[client_count].name, name);
  clients[client_count].balance = 0.00;
  client_count++;
}

void list_all_clients() {
  if (client_count == 0) {
    printf("No clients registered.\n");
    return;
  }

  for (int i = 0; i < client_count; i++) {
    printf("ID: %d | Name: %s | Balance: $%.2f\n", clients[i].id,
           clients[i].name, clients[i].balance);
  }
}

Account* find_client_by_id(int id) {
	for (int i = 0; i < client_count; i++) {
		if (clients[i].id == id) {
			return &clients[i];
		}
	}

	return NULL;
}









