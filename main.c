#include <stdio.h>

struct Account {
  int id;
  char name[50];
  float balance;
};

struct Account clients[3] = {
    {1, "alice", 0.00f},
    {2, "someone", 0.00f},
    {3, "somebody", 100.50f},
};

struct Account *clientsPtr = clients;

int main() {
  for (int i = 0; i < 3; i++) {
    printf("Account %d:\n name: %s\n balance: %.2f\n", (clientsPtr + i)->id,
           (clientsPtr + i)->name, (clientsPtr + i)->balance);
  }

  return 0;
}
