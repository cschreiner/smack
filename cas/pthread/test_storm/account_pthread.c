#include "locks.h"
#include <stdio.h>

#define TRUE 1
#define FALSE 0


// Bank Account Example

// Account structure
typedef struct {
  int balance;
  KSPIN_LOCK lock;
} ACCOUNT, *PACCOUNT;


PACCOUNT create(int b) {
  PACCOUNT acc = (PACCOUNT) malloc(sizeof(ACCOUNT));
  acc->balance = b;
  InitializeSpinLock(&acc->lock);
  return acc;
}

int read(PACCOUNT acc) {
  return acc->balance;
}

void deposit(PACCOUNT acc, int n) {
  AcquireSpinLock(&acc->lock);
  acc->balance = acc->balance + n;
  ReleaseSpinLock(&acc->lock);
}

void withdraw(PACCOUNT acc, int n) {
  int r;
  AcquireSpinLock(&acc->lock);
  r = read(acc);
//  AcquireSpinLock(&acc->lock);
  acc->balance = r - n;
  ReleaseSpinLock(&acc->lock);
}


// Harness

// Thread 1
void deposit_thread(PACCOUNT acc, int n) {
  deposit(acc, n);
}

// Thread 2
void withdraw_thread(PACCOUNT acc, int n) {
  withdraw(acc, n);
}


void storm_main() {
  PACCOUNT acc;
  int x, y, z;

  // Initialization
  x = nondet();
  y = nondet();
  z = nondet();
  acc = create(x);

  // Threads
  __async_call deposit_thread(acc, y); // deposit

  __async_call withdraw_thread(acc, z); // withdraw

  STORM_END;
  STORM_ASSERT(read(acc) == x + y - z);
}

void main() {}

