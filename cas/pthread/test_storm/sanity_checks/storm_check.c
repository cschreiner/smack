#include <stdio.h>
#include "storm.h"

int x;

// Thread 1
void one() {
  // Should fail when executed with 3 contexts per thread
  // because context switches can happen after reads of x,
  // i.e. where || operators are.
  STORM_ASSERT(x == 0 || x == 1 || x == 2)
}

// Thread 2
void two() {
  x = 1;
}

// Thread 3
void three() {
  x = 2;
}


void storm_main() {

  // Initialization
  x = 0;

  // Threads
  __async_call one();

  __async_call two();

  __async_call three();
}

void main() {}

