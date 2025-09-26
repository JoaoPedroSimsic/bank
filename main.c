#include "client.h"

int main() {
  initialize_clients_array(5);

  add_new_client(1, "alice");
  add_new_client(2, "someone");
  add_new_client(3, "somebody");

  printf("--- Listing Clients ---\n");
  list_all_clients();

  Account *found_client = find_client_by_id(2);
  if (found_client != NULL) {
    printf("\nFound client: %s\n", found_client->name);
  } else {
    printf("\nClient not found.\n");
  }

  free(clients); 
  return 0;
}
