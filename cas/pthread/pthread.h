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

/*** **************************************************************************
   *   declarations
   * **************************************************************************
   */

#define _PTHREAD_MAX_THREADS (10)

typedef void* pthread_start_routine_t( void *arg_ptr);

typedef enum { _PTHREAD_STATE_INITIALISED= 0, _PTHREAD_STATE_RUNNING, 
      _PTHREAD_STATE_DONE } 
      _pthread_state_t;

typedef struct {
   /* give this structure a dummy field until something is needed. */
   char dummy;
} pthread_attr_t;

/* main control structure for a thread */
typedef struct {
   _pthread_state_t state;
   const pthread_attr_t attrs;
   void* ret_val;
   
} _pthread_ctl_t;

typedef _pthread_ctl_t* pthread_t;

_pthread_ctl_t _pthread_ctl_array[ _PTHREAD_MAX_THREADS+ 1 ];


/*** ==========================================================================
   *   function prototypes
   */

#define _pthread_set_attr_to_defaults( aa ) { } /* intentionally nothing */

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
void _pthread_ftn_wrapper( pthread_t thread, 
      _pthread_start_routine_t* start_routine_ptr, void* arg_ptr )
{{
   thread_ptr->ret_val= (*start_routine_ptr)(arg_ptr);
   thread_ptr->state= _PTHREAD_STATE_DONE;
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
   *    attr_ptr: pointer to a structure specifying attributes the thread 
   *		should have.
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
int pthread_create( pthread_t* thread_ptr, const pthread_attr_t* attr_ptr,
      pthread_start_routine_t* start_routine_ptr, void* arg_ptr )
{{
   /* find an unused thread control structure */
   int ii;
   for ( ii= 0; ii < _PTHREAD_MAX_THREADS; ii++ ) {
      if ( _pthread_ctl_array[ii]->state= _PTHREAD_STATE_INITIALIZED ) {
         goto found_ctl_struct;
      }
   }
   // apparently no control structures are available
   return EAGAIN;

   found_ctl_struct:

   _pthread_ctl_array[ii]->state= _PTHREAD_STATE_RUNNING;
   if ( attr_ptr == NULL ) {
      _pthread_set_attr_to_defaults( &(_pthread_ctl_array[ii]->attrs) );
      _pthread_ctl_array[ii]->attrs= 
   } else {
      _pthread_ctl_array[ii]->attrs= *attr_ptr;
   }
   *thread_ptr= &_pthread_ctl_array[ii];
   /* TODO: refine the thread start code here */ 
   __SMACK__CODE( "async" ) pthread_ftn_wrapper( 
	 thread_ptr, start_routine_ptr, arg_ptr ); 
   return 0;
}}


/*** --------------------------------------------------------------------------
   * pthread_join()
   * --------------------------------------------------------------------------
   * Description: waits for the given thread to finish, then returns to resume 
   *	execution of the calling thread.
   *
   * Method:
   *
   * Reentrancy:
   *
   * Inputs:
   *   thread: the id of the thread to join
   *   **retval: pointer to where to write the return value, which is itself 
   *		a pointer to void.
   * 
   * Outputs:
   *
   * Return Value: 0 for success, or one of EDEADLK, EINVAL, ESRCH.
   *
   */
int pthread_join( pthread_t thread, void**retval )
{{
   while( thread.state != _PTHREAD_STATE_DONE  ) {
      // do nothing
   }
   *retval= thread->ret_val;
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

