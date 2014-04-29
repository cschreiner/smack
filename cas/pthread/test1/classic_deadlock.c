#include "../spthread.h"
#include <stdio.h>

spthread_mutex_t mutex1, mutex2;
int A_count = 0, B_count = 0;
int A_completion_flag, B_completion_flag= 0;


void * thread_A(void* arg)
{
  spthread_mutex_lock(&mutex1);
  spthread_mutex_lock(&mutex2);
  /* CAS: I'd like to force a task swap here to trigger this deadlock bug */
  A_count++;
  //;;spthread_mutex_unlock(&mutex2);
  //;;spthread_mutex_unlock(&mutex1);

  A_completion_flag= 1;
  return NULL;
}


void * thread_B(void * arg)
{
  spthread_mutex_lock(&mutex2);
  spthread_mutex_lock(&mutex1);
  /* CAS: I'd like to force a task swap here to trigger this deadlock bug */
  B_count++;
  //;;spthread_mutex_unlock(&mutex1);
  //;;spthread_mutex_unlock(&mutex2);

  B_completion_flag= 1;
  return NULL;
}



int main()
{

  spthread_mutex_init(&mutex1,NULL);
  spthread_mutex_init(&mutex2,NULL);

  spthread_t a1, b1;

  spthread_create(&a1, NULL, thread_A, NULL);
  
  spthread_create(&b1, NULL, thread_B, NULL);

  spthread_join(a1, NULL);
  spthread_join(b1, NULL);

  __SMACK_assert( A_completion_flag == 1 );
  __SMACK_assert( B_completion_flag == 1 );

  /* since this assert() never fires, I conclude that SMACK has correctly
     detected that the deadlock means there thare no viable execution paths
     before we reach this point, and has therefore concluded the program will
     already have ceased running.  Since all asserts pass up to the time the
     program ceases to run, SMACK declares the program a success. -- CAS
   */
  __SMACK_assert( 0 );;

  return 0;
}
