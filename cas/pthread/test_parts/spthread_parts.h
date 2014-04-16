/*** 
   * Program Name: SMACK spthreads
   *
   * File Name: spthread.h
   *
   * File Description: 
   *
   * SMACK spthreads was written by Christian A. Schreiner at University of
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

#if !defined(__SPTHREAD_H__)
#define __SPTHREAD_H__

/*** **************************************************************************
   *   includes
   * **************************************************************************
   */
#include <stdlib.h>
#include <errno.h>

/*** **************************************************************************
   *   stuff to add to smack.h or similar
   * **************************************************************************
   */
#include "/uusoc/scratch/euler/cas/tuut/x86_64/smack-project/smack/install/include/smack/smack.h"


/*** **************************************************************************
   *   declarations
   * **************************************************************************
   */
#define _SPTHREAD_MAX_THREADS (2)

typedef void* spthread_start_routine_t( void *arg_ptr);

typedef enum { _SPTHREAD_STATE_FIRST= 0x8887, // random num 1...32767
      _SPTHREAD_STATE_INITIALIZED, _SPTHREAD_STATE_RUNNING, 
      _SPTHREAD_STATE_DONE,
      _SPTHREAD_STATE_LAST } _spthread_state_t;

/* main control structure for a thread */
typedef struct {
   _spthread_state_t state;
} _spthread_ctl_t;

typedef _spthread_ctl_t* spthread_t;

_spthread_ctl_t _spthread_ctl_array[ _SPTHREAD_MAX_THREADS+ 1 ];
/* Note: each element in this array should be initialized when
   pthread_create() initializes it. 
*/


/* ..........................................................................
   locking structures
*/
typedef enum { _SPTHREAD_MUTEX_VAL_FIRST= -1, _SPTHREAD_MUTEX_VAL_UNLOCKED= 0,
      _SPTHREAD_MUTEX_VAL_LOCKED, _SPTHREAD_MUTEX_VAL_LAST } 
      _spthread_mutex_val_t;

typedef struct {
   _spthread_mutex_val_t lock;
} spthread_mutex_t;


/*** ==========================================================================
   *   function prototypes
   */

/*** --------------------------------------------------------------------------
   * _spthread_ftn_wrapper()
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
void _spthread_ftn_wrapper( spthread_t thread, 
      spthread_start_routine_t* start_routine_ptr, void* arg_ptr )
{{
   (*start_routine_ptr)(arg_ptr);
   thread->state= _SPTHREAD_STATE_DONE;
   /* TODO2: find some way to move unused threads from state
      _SPTHREAD_STATE_DONE back to _SPTHREAD_STATE_INITIALIZED so the control
      structure can be reused.
    */
}}


/*** --------------------------------------------------------------------------
   * spthread_create()
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
int spthread_create( spthread_t* thread_ptr, 
      spthread_start_routine_t* start_routine_ptr, void* arg_ptr )
{{
   /* find an unused thread control structure */
   int ii;
   for ( ii= 0; ii < _SPTHREAD_MAX_THREADS; ii++ ) {
      if ( _spthread_ctl_array[ii].state!= _SPTHREAD_STATE_RUNNING ) {
         goto found_ctl_struct;
      }
   }
   // apparently no control structures are available
   return EAGAIN;

   found_ctl_struct:

   _spthread_ctl_array[ii].state= _SPTHREAD_STATE_RUNNING;
   *thread_ptr= &_spthread_ctl_array[ii];
   /* TODO: double check the thread start code here */ 
   __SMACK_code( "call {:ASYNC} _spthread_ftn_wrapper( " 
	 "thread_ptr, start_routine_ptr, arg_ptr );" ); 

   return 0;
}}

/*** --------------------------------------------------------------------------
   * spthread_mutex_init()
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
int spthread_mutex_init( spthread_mutex_t* mutex_ptr )
{{
   mutex_ptr->lock= _SPTHREAD_MUTEX_VAL_UNLOCKED;
   return 0;
}}


/*** --------------------------------------------------------------------------
   * spthread_mutex_lock()
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
int spthread_mutex_lock( spthread_mutex_t* mutex_ptr )
{{
   int retval= 0;
   _spthread_mutex_val_t lock_status= _SPTHREAD_MUTEX_VAL_UNLOCKED;

   __SMACK_top_decl( "procedure corral_atomic_begin();" );
   __SMACK_top_decl( "procedure corral_atomic_end();" );

   retval= 0;

   /* match the AcquireSpinLock() function in storm's locks.h:
      mutex_ptr->lock corresponds to __resource("LOCK", SpinLock).
      _SPTHREAD_MUTEX_VAL_UNLOCKED corresponds to UNLOCKED.
      _SPTHREAD_MUTEX_VAL_LOCKED corresponds to storm_getThreadID() aka tid.
    */
   __SMACK_code( "call corral_atomic_begin();" );

   __SMACK_assume( mutex_ptr->lock == lock_status );
   __SMACK_assert( _SPTHREAD_MUTEX_VAL_LOCKED != lock_status );
   __SMACK_assume( lock_status == _SPTHREAD_MUTEX_VAL_UNLOCKED );
   mutex_ptr->lock= _SPTHREAD_MUTEX_VAL_LOCKED;

   __SMACK_code( "call corral_atomic_end();" );
   /* end match */

   return retval;
}}

/*** --------------------------------------------------------------------------
   * spthread_mutex_unlock()
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
int spthread_mutex_unlock( spthread_mutex_t* mutex_ptr )
{{
   _spthread_mutex_val_t lock_status= _SPTHREAD_MUTEX_VAL_UNLOCKED;

   __SMACK_top_decl( "procedure corral_atomic_begin();" );
   __SMACK_top_decl( "procedure corral_atomic_end();" );

   int retval= 0;

   /* match the ReleaseSpinLock() function in storm's locks.h:
      mutex_ptr->lock corresponds to __resource("LOCK", SpinLock).
      _SPTHREAD_MUTEX_VAL_UNLOCKED corresponds to UNLOCKED.
      _SPTHREAD_MUTEX_VAL_LOCKED corresponds to storm_getThreadID() aka tid.
    */
   __SMACK_code( "call corral_atomic_begin();" );

   __SMACK_assume( mutex_ptr->lock == lock_status );
   __SMACK_assert( lock_status == _SPTHREAD_MUTEX_VAL_LOCKED );
   mutex_ptr->lock= _SPTHREAD_MUTEX_VAL_UNLOCKED;

   __SMACK_code( "call corral_atomic_end();" );
   /* end match */

   return retval;
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
#endif /* !defined(__SPTHREAD_H__) */

