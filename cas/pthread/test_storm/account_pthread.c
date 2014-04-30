#include <stdio.h>
#include <stdlib.h>
#include <smack.h>
#include <pthread.h>

#define TRUE 1
#define FALSE 0


// Bank Account Example

// Account structure
typedef struct {
  int balance;
  pthread_mutex_t lock;
} account_t, *account_ptr_t;


account_ptr_t create(int b) {
  account_ptr_t acc = (account_ptr_t) malloc(sizeof(account_t));
  acc->balance = b;
  pthread_mutex_init(&(acc->lock), &PTHREAD_MUTEX_INITIALIZER );
  return acc;
}

int read(account_ptr_t acc) {
  return acc->balance;
}

void deposit(account_ptr_t acc, int n) {
  pthread_mutex_lock(&acc->lock);
  acc->balance = acc->balance + n;
  pthread_mutex_unlock(&acc->lock);
}

void withdraw(account_ptr_t acc, int n) {
  int r;
  pthread_mutex_lock(&acc->lock);
  r = read(acc); // why are we storing balance in a local var?
  acc->balance = r - n;
  pthread_mutex_unlock(&acc->lock);
}


// =========================================================================
// Harness

typedef struct {
   account_ptr_t acc;
   int amt;
} thread_arg_t;

// Thread 1
void* deposit_thread( void* aa ) {
  thread_arg_t* aa2= (thread_arg_t*) aa;
  deposit( aa2->acc, aa2->amt );
  return NULL;
}

// Thread 2
void* withdraw_thread( void* aa ) {
  thread_arg_t* aa2= (thread_arg_t*) aa;
  withdraw( aa2->acc, aa2->amt );
  return NULL;
}


// =========================================================================
int main() {
  account_ptr_t acc;
  int x, y, z;
  pthread_t deposit_thread_ctl, withdraw_thread_ctl;
  thread_arg_t deposit_args, withdraw_args;
  void* retval;

  // Initialization
  x = __SMACK_nondet();
  y = __SMACK_nondet();
  z = __SMACK_nondet();
  acc = create(x);
  deposit_args= (thread_arg_t){ acc, y };
  withdraw_args= (thread_arg_t){ acc, z };


  // Threads
  pthread_create( &deposit_thread_ctl, NULL, deposit_thread, &deposit_args  );
  pthread_create( &withdraw_thread_ctl, NULL, withdraw_thread, &withdraw_args );
  pthread_join( deposit_thread_ctl, &retval );
  pthread_join( withdraw_thread_ctl, &retval );

  __SMACK_assert(read(acc) == x + y - z);
}


// =========================================================================
// end of file
