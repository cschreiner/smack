#error calls functions not supported by smack pthreads as of 2014apr28.
#include "../spthread.h"
#include <stdio.h>
#include <assert.h>

#define QUEUE_FULL_SIZE 1

// global variables
spthead_mutex_t mux;
spthead_cond_t  cond_full;
spthead_cond_t  cond_empty;

int qsize;

int static counter = 0;

// producer thread
void* producer(int * procid)
{
  int i;
    for (i = 0; i < 1; i ++) {
      //    while (1) {
    spthead_mutex_lock(&mux);
    
    while (qsize == QUEUE_FULL_SIZE)
      spthead_cond_wait(&cond_full, &mux);

    assert(qsize >= 0);
    assert(qsize <= QUEUE_FULL_SIZE);
    
    printf("%d  produces %d, item, qsize = %d\n", *procid, counter , qsize);
    counter ++;
    spthead_cond_signal(&cond_empty);
    
   // sleep(1);
    qsize ++;    
    spthead_mutex_unlock(&mux);
    }
    return NULL;
}


// consumer thread
void* consumer(int * procid)
{
  int val, i;

    for (i = 0; i < 1; i ++) {
      //    while (1) {
    spthead_mutex_lock(&mux);
    
    while (qsize == 0) // was if in the buggy code
      spthead_cond_wait(&cond_empty, &mux);

    assert(qsize >= 0); 
    assert(qsize <= QUEUE_FULL_SIZE);    

    printf("%d consumed %d,  item, qsize = %d \n", *procid, val, qsize);
    spthead_cond_signal(&cond_full);
    
    qsize --;
    spthead_mutex_unlock(&mux);
    }
    return NULL;
}


// main procedure
int main()
{
  int i, ret1, ret2;

  spthead_t prod[2];
  spthead_t cons[2];

  qsize = 0;

  spthead_mutex_init(&mux, NULL);
  spthead_cond_init(&cond_full, NULL);
  spthead_cond_init(&cond_empty, NULL);

  for (i = 0; i < 2; i ++) {
    ret1 = spthead_create(&prod[i], NULL, producer, &i);
    ret2 = spthead_create(&cons[i], NULL, consumer, &i);

    if (ret1 != 0 || ret2 != 0) {
      //cout << "Error creating threads." << endl;
      exit(-1);
    }
  }
  //  spthead_exit(NULL);
  for (i = 0; i < 2; i ++) {
    spthead_join(prod[i], NULL);
    spthead_join(cons[i], NULL);
  }

  spthead_mutex_destroy(&mux);
  spthead_cond_destroy(&cond_full);
  spthead_cond_destroy(&cond_empty);
    return NULL;
}
