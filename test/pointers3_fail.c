#include <stdio.h>
#include <stdlib.h>
#include "smack.h"

typedef struct {
  int a;
  int b;
} point;

point p;

void incr(point *p) {
  p->a += 2;
  p->b += 2;
}

void decr(point *p) {
  p->a--;
  p->b--;
}

void foo(void) {
  p.a = p.b = 1;
  incr(&p);
  decr(&p);
}

void bar(void) {
  __SMACK_assert(p.a == 1);
  __SMACK_assert(p.b == 1);
}

int main() {
  foo();
  bar();
  return 0;
}

