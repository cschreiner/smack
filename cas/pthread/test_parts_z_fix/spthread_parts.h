/*** 
   * Program Name: SMACK pthreads
   *
   * File Name: pthread.h
   *
   * File Description: 
   *
   * SMACK pthreads was written by Christian A. Schreiner at University of
   * Utah.  Copyright (C) 2014-2014 by University of Utah.  All rights
   * reserved.  You may use, examine, or modify this file only in accordance
   * with the GNU Public License, or, alternately, by special written
   * arrangement with the author.  This file comes with no warranties.  If you
   * use it and something breaks, you are solely responsible for cleaning up
   * afterwards.
   *
   */

/*** Configuration Management Information:
   * 
   * $Source: $
   * $Author: $
   * $Date: $
   * $Revision: $
   * 
   */

#if !defined(__PTHREAD_H__)
#define __PTHREAD_H__

/*** **************************************************************************
   *   includes
   * **************************************************************************
   */
#include <stdlib.h>
#include <errno.h>

#include <smack.h>


/*** **************************************************************************
   *   declarations
   * **************************************************************************
   */
#define _PTHREAD_MAX_THREADS (2)

typedef void* pthread_start_routine_t( void *arg_ptr);

/* main control structure for a thread */
typedef struct {
   char dummy;
} pthread_t;

/* ..........................................................................
   locking structures
*/
typedef enum { _PTHREAD_MUTEX_VAL_UNLOCKED= 0, _PTHREAD_MUTEX_VAL_LOCKED }
      _pthread_mutex_val_t;

typedef struct {
   _pthread_mutex_val_t lock;
} pthread_mutex_t;


/*** ==========================================================================
   *   function prototypes
   */

/*** --------------------------------------------------------------------------
   * _pthread_ftn_wrapper()
   * --------------------------------------------------------------------------
   * Description: manages the thread's start function, and its return value. 
   *	Runs as part of the started thread, not as part of the calling thread.
   *
   * Method:
   *
   * Reentrancy:
   *
   * Inputs:
   *    thread_ptr: pointer to the thread structure to control the thread.
   *	start_routine_ptr: pointer to the function that the thread should 
   *		run first.  
   *    arg_ptr: pointer to the single argument to pass to the start routine.
   * 
   * Outputs: none
   *
   * Return Value: void
   *
   */
void _pthread_ftn_wrapper( pthread_t* thread, 
      pthread_start_routine_t* start_routine_ptr, void* arg_ptr )
{{
   (*start_routine_ptr)(arg_ptr);
}}


/*** --------------------------------------------------------------------------
   * pthread_create()
   * --------------------------------------------------------------------------
   * Description: starts a new thread running
   *
   * Method:
   *
   * Reentrancy:
   *
   * Inputs:
   *    thread_ptr: pointer to the thread structure to control the thread.
   *	start_routine_ptr: pointer to the function that the thread should 
   *		run first.  
   *    arg_ptr: pointer to the single argument to pass to the start routine.
   *		
   * 
   * Outputs:
   *
   * Return Value:
   *
   */
int pthread_create( pthread_t* thread_ptr, 
      pthread_start_routine_t* start_routine_ptr, void* arg_ptr )
{{

   int tmp = __SMACK_nondet();
   __SMACK_code("assume @ == 0;", tmp);
   if (tmp)  {
      _pthread_ftn_wrapper(thread_ptr, start_routine_ptr, arg_ptr); 
      // Required workaround to get pointer analysis to work properly in 
      // the presence of __SMACK_code.
   }
   __SMACK_code( "async call _pthread_ftn_wrapper(@, @, @);", 
	 thread_ptr, start_routine_ptr, arg_ptr); 

   return 0;
}}

/*** --------------------------------------------------------------------------
   * pthread_mutex_init()
   * --------------------------------------------------------------------------
   * Description: initializes a mutex lock
   *
   * Method:
   *
   * Reentrancy:
   *
   * Inputs:
   *   mutex_ptr: indicates the lock to initialize
   * 
   * Outputs: none
   *
   * Return Value: always returns 0
   *
   * TODO2: add support for RECURSIVE and ERRORCHECK mutexes. 
   */
int pthread_mutex_init( pthread_mutex_t* mutex_ptr )
{{
   mutex_ptr->lock= _PTHREAD_MUTEX_VAL_UNLOCKED;
   return 0;
}}


/*** --------------------------------------------------------------------------
   * pthread_mutex_lock()
   * --------------------------------------------------------------------------
   * Description: gets a mutex lock
   *
   * Method: uses these Corral functions: 
   *	procedure corral_atomic_begin();
   *	procedure corral_atomic_end();
   *
   * Reentrancy:
   *
   * Inputs:
   *   mutex_ptr: indicates the lock to get
   * 
   * Outputs: none
   *
   * Return Value: if success, 0.
   *   If the lock contents are uninitialized, EINVAL.  
   *
   * TODO2: add support for RECURSIVE and ERRORCHECK mutexes. 
   */
int pthread_mutex_lock( pthread_mutex_t* mutex_ptr )
{{
   __SMACK_top_decl( "procedure corral_atomic_begin();" );
   __SMACK_top_decl( "procedure corral_atomic_end();" );

   /* match the AcquireSpinLock() function in storm's locks.h:
      mutex_ptr->lock corresponds to __resource("LOCK", SpinLock).
      _PTHREAD_MUTEX_VAL_UNLOCKED corresponds to UNLOCKED.
      _PTHREAD_MUTEX_VAL_LOCKED corresponds to storm_getThreadID() aka tid.
    */
   __SMACK_code( "call corral_atomic_begin();" );

   __SMACK_assume( mutex_ptr->lock == _PTHREAD_MUTEX_VAL_UNLOCKED );
   mutex_ptr->lock= _PTHREAD_MUTEX_VAL_LOCKED;

   __SMACK_code( "call corral_atomic_end();" );
   /* end match */

   return 0;
}}

/*** --------------------------------------------------------------------------
   * pthread_mutex_unlock()
   * --------------------------------------------------------------------------
   * Description: releases a lock so other threads can use the associated 
   *	resource
   *
   * Method:
   *
   * Reentrancy:
   *
   * Inputs:
   *   mutex_ptr: indicates the lock structure to use
   * 
   * Outputs: none
   *
   * Return Value: if success, 0.
   *	EINVAL if the lock is already unlocked.
   *
   *
   * TODO2: add support for RECURSIVE and ERRORCHECK mutexes. 
   */
int pthread_mutex_unlock( pthread_mutex_t* mutex_ptr )
{{
   __SMACK_top_decl( "procedure corral_atomic_begin();" );
   __SMACK_top_decl( "procedure corral_atomic_end();" );

   /* match the ReleaseSpinLock() function in storm's locks.h:
      mutex_ptr->lock corresponds to __resource("LOCK", SpinLock).
      _PTHREAD_MUTEX_VAL_UNLOCKED corresponds to UNLOCKED.
      _PTHREAD_MUTEX_VAL_LOCKED corresponds to storm_getThreadID() aka tid.
    */
   __SMACK_code( "call corral_atomic_begin();" );

   __SMACK_assume( mutex_ptr->lock == _PTHREAD_MUTEX_VAL_LOCKED );
   mutex_ptr->lock= _PTHREAD_MUTEX_VAL_UNLOCKED;

   __SMACK_code( "call corral_atomic_end();" );
   /* end match */

   return 0;
}}



// template is 17 lines long.
/*** --------------------------------------------------------------------------
   * name()
   * --------------------------------------------------------------------------
   * Description: 
   *
   * Method: 
   *
   * Reentrancy: 
   *
   * Inputs: 
   *	 
   * Outputs: 
   *	
   * Return Value: 
   *
   */


/*** **************************************************************************
   *   end of file
   * **************************************************************************
   */
#endif /* !defined(__PTHREAD_H__) */

