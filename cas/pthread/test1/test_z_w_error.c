#include <stdlib.h>
#include "/uusoc/scratch/euler/cas/tuut/x86_64/smack-project/smack/install/include/smack/smack.h"
#include "/uusoc/scratch/euler/cas/edu/uut/smack/cas/pthread/spthread.h"

int x = 1;

void *my_procedure(void *my_argument) {
  x = 0;
  return 0;
}

void *another(void *my_argument) {
  __SMACK_assert(x > 0);
  return 0;
}

spthread_t thread1_ctl, thread2_ctl;

int main() {
   spthread_create(&thread1_ctl, NULL, my_procedure, 0);
   spthread_create(&thread2_ctl, NULL, another, 0);
   return 0;
}

