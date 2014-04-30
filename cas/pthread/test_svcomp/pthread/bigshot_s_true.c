/* from:
https://svn.sosy-lab.org/software/sv-benchmarks/tags/svcomp14/pthread/bigshot_s_true.c
*/

#include <stdlib.h>
#include <string.h>

#include <smack.h>
#include <pthread.h>

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
  pthread_t t1, t2;

  pthread_create(&t1, 0, thread1, 0);
  pthread_join(t1, 0);

  pthread_create(&t2, 0, thread2, 0);
  pthread_join(t2, 0);

  __SMACK_assert(!v || v[0] == 'B');

  return 0;
}

