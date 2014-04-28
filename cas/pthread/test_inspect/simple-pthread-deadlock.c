#include "../spthread.h"
#include <stdio.h>

spthread_mutex_t  mutex, lock;
int A_count = 0, B_count = 0;


void * thread_A(void* arg)
{
  spthread_mutex_lock(&mutex);
  A_count++;
  if (A_count == 1) 
    spthread_mutex_lock(&lock);
  spthread_mutex_unlock(&mutex);

  spthread_mutex_lock(&mutex);
  A_count--;
  if (A_count == 0) 
    spthread_mutex_unlock(&lock);
  spthread_mutex_unlock(&mutex);
}


void * thread_B(void * arg)
{
  spthread_mutex_lock(&mutex);
  B_count++;
  if (B_count == 1) 
    spthread_mutex_lock(&lock);
  spthread_mutex_unlock(&mutex);

  spthread_mutex_lock(&mutex);
  B_count--;
  if (B_count == 0) 
    spthread_mutex_unlock(&lock);
  spthread_mutex_unlock(&mutex);

}



int main()
{

  spthread_mutex_init(&mutex,NULL);
  spthread_mutex_init(&lock,NULL);

  spthread_t a1, a2, b1, b2;

  spthread_create(&a1, NULL, thread_A, NULL);
  
  spthread_create(&b1, NULL, thread_B, NULL);

  spthread_join(a1, NULL);
  spthread_join(b1, NULL);

  return 0;
}
