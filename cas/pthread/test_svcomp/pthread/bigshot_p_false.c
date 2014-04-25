#include <stdlib.h>
#include "/uusoc/scratch/euler/cas/tuut/x86_64/smack-project/smack/install/include/smack/smack.h"
#include "/uusoc/scratch/euler/cas/edu/uut/smack/cas/pthread/spthread.h"
#include <string.h>


char *v;

void *thread1(void * arg)
{
  v = malloc(sizeof(char) * 8);
  return NULL;
}

void *thread2(void *arg)
{
  if (v) strcpy(v, "Bigshot");
  return NULL;
}


int main()
{
  spthread_t t1, t2;

  spthread_create(&t1, 0, thread1, 0);
  spthread_create(&t2, 0, thread2, 0);
  spthread_join(t1, 0);
  spthread_join(t2, 0);

  __SMACK_assert(!v || v[0] == 'B');

  return 0;
}

