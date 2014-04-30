//#include <pthread.h>
#include <stdio.h>
#include <assert.h>

#include <smack.h>
#include <pthread.h>

#define QUEUE_FULL_SIZE 1

// global variables
pthread_mutex_t mux;
pthread_cond_t  cond_full;
pthread_cond_t  cond_empty;

int qsize;

int static counter = 0;

// producer thread
void* producer(int * procid)
{
  int i;
    for (i = 0; i < 1; i ++) {
      //    while (1) {
    pthread_mutex_lock(&mux);
    
    while (qsize == QUEUE_FULL_SIZE)
      pthread_cond_wait(&cond_full, &mux);

    assert(qsize >= 0);
    assert(qsize <= QUEUE_FULL_SIZE);
    
    printf("%d  produces %d, item, qsize = %d\n", *procid, counter , qsize);
    counter ++;
    pthread_cond_signal(&cond_empty);
    
   // sleep(1);
    qsize ++;    
    pthread_mutex_unlock(&mux);
    }
    return NULL;
}


// consumer thread
void* consumer(int * procid)
{
  int val, i;

    for (i = 0; i < 1; i ++) {
      //    while (1) {
    pthread_mutex_lock(&mux);
    
    while (qsize == 0) // was if in the buggy code
      pthread_cond_wait(&cond_empty, &mux);

    assert(qsize >= 0);
    assert(qsize <= QUEUE_FULL_SIZE);    

    printf("%d co
nsumed %d,  item, qsize = %d \n", *procid, val, qsize);
    pthread_cond_signal(&cond_full);
    
    qsize --;
    pthread_mutex_unlock(&mux);
    }
    return NULL;
}


// main procedure
int main()
{
  int i, ret1, ret2;

  pthread_t prod[2];
  pthread_t cons[2];

  qsize = 0;

  pthread_mutex_init(&mux, NULL);
  pthread_cond_init(&cond_full, NULL);
  pthread_cond_init(&cond_empty, NULL);

  for (i = 0; i < 2; i ++) {
    ret1 = pthread_create(&prod[i], NULL, producer, &i);
    ret2 = pthread_create(&cons[i], NULL, consumer, &i);

    if (ret1 != 0 || ret2 != 0) {
      //cout << "Error creating threads." << endl;
      exit(-1);
    }
  }
  //  pthread_exit(NULL);
  for (i = 0; i < 2; i ++) {
    pthread_join(prod[i], NULL);
    pthread_join(cons[i], NULL);
  }

  pthread_mutex_destroy(&mux);
  pthread_cond_destroy(&cond_full);
  pthread_cond_destroy(&cond_empty);
    return NULL;
}
