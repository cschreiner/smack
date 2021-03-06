#include <stdlib.h>
#include "smack.h"

void incr(int *x) {
  (*x)++;
}

void decr(int *x) {
  (*x)--;
}

int main(void) {
  void (*fp)(int*);
  int *x = (int*)malloc(sizeof(int));
  int y = 1;

  *x = 1;
  if (y > 0) {
    fp = incr;
  } else {
    fp = decr;
  }
  fp(x);

  __SMACK_assert(*x == 2);
  return 0;
}

