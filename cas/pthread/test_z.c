#include <stdlib.h>
#include <smack.h>

int x = 1;

void *my_procedure(void *my_argument) {
  x = 0;
  return 0;
}

void *another(void *my_argument) {
  __SMACK_assert(x > 0);
  return 0;
}

void call_something(void *(*proc)(void*), void *arg) {
  proc(arg);
}

void pthread_create(void *(*proc)(void*), void *arg) {
  __SMACK_code("call {:ASYNC} call_something(proc,arg);");
}

int main() {
  pthread_create(my_procedure, 0);
  pthread_create(another,0);
  return 0;
}

