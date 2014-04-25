/* from:
https://svn.sosy-lab.org/software/sv-benchmarks/tags/svcomp14/pthread/bigshot_s_true.c
*/

#include <stdlib.h>
#include "/uusoc/scratch/euler/cas/tuut/x86_64/smack-project/smack/install/include/smack/smack.h"
#include "/uusoc/scratch/euler/cas/edu/uut/smack/cas/pthread/spthread.h"
#include <string.h>


char *v;

void *thread1(void * arg)
{
  v = malloc(sizeof(char) * 8);
}

void *thread2(void *arg)
{
  if (v) strcpy(v, "Bigshot");
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

