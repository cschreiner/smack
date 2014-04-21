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

#include "/uusoc/scratch/euler/cas/tuut/x86_64/smack-project/smack/install/include/smack/smack.h"


/*** **************************************************************************
   *   declarations
   * **************************************************************************
   */
#define _SPTHREAD_MAX_THREADS (2)

typedef void* spthread_start_routine_t( void *arg_ptr);

/* main control structure for a thread */
typedef struct {
   char dummy;
} spthread_t;

/* ..........................................................................
   locking structures
*/
typedef enum { _SPTHREAD_MUTEX_VAL_UNLOCKED= 0, _SPTHREAD_MUTEX_VAL_LOCKED }
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
void _spthread_ftn_wrapper( spthread_t* thread, 
      spthread_start_routine_t* start_routine_ptr, void* arg_ptr )
{{
   (*start_routine_ptr)(arg_ptr);
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
   #if 1 
      /* workaround to get pointer analysis to work properly in the 
	 presence of __SMACK_code(). 
      */
      int tmp= __SMACK_nondet();
      __SMACK_code( "assume @ == 0;", tmp );
      if ( tmp ) {
	 _spthread_ftn_wrapper( thread_ptr, start_routine_ptr, arg_ptr );
      }
   #endif
  
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

   __SMACK_code( "call corral_atomic_begin();" );

   __SMACK_assume( mutex_ptr->lock == _SPTHREAD_MUTEX_VAL_UNLOCKED );
   mutex_ptr->lock= _SPTHREAD_MUTEX_VAL_LOCKED;

   __SMACK_code( "call corral_atomic_end();" );

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
   int retval= 0;

   __SMACK_code( "call corral_atomic_begin();" );

   __SMACK_assume( mutex_ptr->lock == _SPTHREAD_MUTEX_VAL_LOCKED );
   mutex_ptr->lock= _SPTHREAD_MUTEX_VAL_UNLOCKED;

   __SMACK_code( "call corral_atomic_end();" );

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

