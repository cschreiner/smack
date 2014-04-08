/* test_all_spthread.c
 *   
 * tests _all_ of spthread.h's create capability.
 */

#include <stdlib.h>
#include "/uusoc/scratch/euler/cas/tuut/x86_64/smack-project/smack/install/include/smack/smack.h"
#include "spthread.h"

spthread_attr_t attrs;

int x = 1;

void *my_procedure(void *my_argument) {
  x = 0;
  return 0;
}

void *another(void *my_argument) {
  __SMACK_assert(x > 0);
  return 0;
}

int main() {
   spthread_t my_procedures_thread_ctl, another_thread_ctl;
   spthread_create( &my_procedures_thread_ctl, &attrs, my_procedure, 0);
   spthread_create( &another_thread_ctl, &attrs, another, 0);
   return 0;
}

