#include <stdlib.h>
#include "/uusoc/scratch/euler/cas/tuut/x86_64/smack-project/smack/install/include/smack/smack.h"
#include "spthread_parts.h"

int x = 1;
spthread_t my_proc_thread_ctl, another_thread_ctl;

void *my_procedure(void *my_argument) {
  x = 0;
  return 0;
}

void *another(void *my_argument) {
  __SMACK_assert(x > 0); // this should fail
  return 0;
}

int main() {
   spthread_create(&my_proc_thread_ctl, my_procedure, 0);
   spthread_create(&another_thread_ctl, another, 0);
   return 0;
}

