/*****************************************************************************
* FILE: bug6fix.c
* DESCRIPTION:
*   This solution uses a mutex variable to protect the global sum while each
*   thread updates it. A much more efficient method would be that used in the
*   dotprod_mutex.c example.
* SOURCE: 07/06/05 Blaise Barney
* LAST REVISED: 01/29/09 Blaise Barney
******************************************************************************/
#error calls functions not supported by smack pthreads as of 2014apr28.
#include <stdio.h>
#include <stdlib.h>

#include <smack.h>
#include <spthread.h>

/* Define global data where everyone can see them */
#define NUMTHRDS 2
#define VECLEN 10000
spthread_mutex_t mutexsum;
int *a, *b; 
long sum=0.0;

void *dotprod(void *arg)
{
  /* Each thread works on a different set of data.
   * The offset is specified by the arg parameter. The size of
   * the data for each thread is indicated by VECLEN.
   */
   int i, start, end, offset, len;
   long tid;
   tid = (long)arg;
   offset = tid;
   len = VECLEN;
   start = offset*len;
   end   = start + len;

/* Perform my section of the dot product */
   printf("thread: %ld starting. start=%d end=%d\n",tid,start,end-1);
   for (i=start; i<end ; i++) {
      spthread_mutex_lock(&mutexsum);
      sum += (a[i] * b[i]);
      spthread_mutex_unlock(&mutexsum);
      }
   printf("thread: %ld done. Global sum now is=%li\n",tid,sum);

   spthread_exit((void*) 0);
}

int main (int argc, char *argv[])
{
long i;
void *status;
spthread_t threads[NUMTHRDS];
spthread_attr_t attr;

/* Assign storage and initialize values */
a = (int*) malloc (NUMTHRDS*VECLEN*sizeof(int));
b = (int*) malloc (NUMTHRDS*VECLEN*sizeof(int));
  
for (i=0; i<VECLEN*NUMTHRDS; i++)
  { a[i]=1;
    b[i]=1; }

/* Initialize mutex variable */
spthread_mutex_init(&mutexsum, NULL);
         
/* Create threads as joinable, each of which will execute the dot product
 * routine. Their offset into the global vectors is specified by passing
 * the "i" argument in pthread_create().
 */
spthread_attr_init(&attr);
spthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
for(i=0;i<NUMTHRDS;i++)
   spthread_create(&threads[i], &attr, dotprod, (void *)i); 

spthread_attr_destroy(&attr);

/* Wait on the other threads for final result */

for(i=0;i<NUMTHRDS;i++) {
  spthread_join(threads[i], &status);
  }
/* After joining, print out the results and cleanup */
printf ("Final Global Sum=%li\n",sum);
free (a);
free (b);
spthread_mutex_destroy(&mutexsum);
spthread_exit(NULL);
}   

