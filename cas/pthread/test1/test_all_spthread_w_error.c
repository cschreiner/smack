/* test_all_pthread.c
 *   
 * tests _all_ of pthread.h's create capability.
 */
#include <stdlib.h>

#include <smack.h>
#include <pthread.h>

pthread_attr_t attrs;

int x = 1;

void *my_procedure(void *my_argument) {
  x = 0;
  return 0;
}

void *another(void *my_argument) {
  __SMACK_assert(x > 0); // ERROR: but x was set to 0, so it can't exceed 0
  return 0;
}

int main() {
   pthread_t my_procedures_thread_ctl, another_thread_ctl;
   pthread_create( &my_procedures_thread_ctl, &attrs, my_procedure, 0);
   pthread_create( &another_thread_ctl, &attrs, another, 0);
   return 0;
}

