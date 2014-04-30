/* from:
https://svn.sosy-lab.org/software/sv-benchmarks/tags/svcomp14/pthread/bigshot_s_true.c
*/

#include <stdlib.h>
#include <string.h>

#include <smack.h>
#include <spthread.h>

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
  spthread_join(t1, 0);

  spthread_create(&t2, 0, thread2, 0);
  spthread_join(t2, 0);

  __SMACK_assert(!v || v[0] == 'B');

  return 0;
}

