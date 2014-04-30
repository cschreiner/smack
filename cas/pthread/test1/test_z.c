#include <stdlib.h>
#include <smack.h>
#include <pthread.h>

int x = 1;

void *my_procedure(void *my_argument) {
  x = 10;
  return 0;
}

void *another(void *my_argument) {
  __SMACK_assert(x > 0);
  return 0;
}

pthread_t thread1_ctl, thread2_ctl;

int main() {
   pthread_create(&thread1_ctl, NULL, my_procedure, 0);
   pthread_create(&thread2_ctl, NULL, another, 0);
   return 0;
}

