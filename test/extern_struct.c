#include "smack.h"

extern const struct process *procinit[];

int main(void) {
  procinit[0] = 0;
  __SMACK_assert(0);
  return 0;
}

