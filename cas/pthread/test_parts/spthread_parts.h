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
   *   declarations
   * **************************************************************************
   */

#define _SPTHREAD_MAX_THREADS (10)

typedef void* spthread_start_routine_t( void *arg_ptr);

typedef enum { _SPTHREAD_STATE_INITIALIZED= 0, _SPTHREAD_STATE_RUNNING, 
      _SPTHREAD_STATE_DONE } 
      _spthread_state_t;

typedef struct {
   /* give this structure a dummy field until something is needed. */
   char dummy;
} spthread_attr_t;

/* main control structure for a thread */
typedef struct {
   _spthread_state_t state;
   spthread_attr_t attrs;
   void* ret_val;
   
} _spthread_ctl_t;

typedef _spthread_ctl_t* spthread_t;

_spthread_ctl_t _spthread_ctl_array[ _SPTHREAD_MAX_THREADS+ 1 ];



/*** ==========================================================================
   *   function prototypes
   */

#define _spthread_set_attr_to_defaults( aa ) { } /* intentionally nothing */

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
   thread->ret_val= (*start_routine_ptr)(arg_ptr);
   thread->state= _SPTHREAD_STATE_DONE;
   /* TODO2: find some way to move unused threads from state
      _SPTHREAD_STATE_DONE bacvk to _SPTHREAD_STATE_INITIALIZED so the control
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
int spthread_create( spthread_t* thread_ptr, const spthread_attr_t* attr_ptr,
      spthread_start_routine_t* start_routine_ptr, void* arg_ptr )
{{
   /* find an unused thread control structure */
   int ii;
   for ( ii= 0; ii < _SPTHREAD_MAX_THREADS; ii++ ) {
      if ( _spthread_ctl_array[ii].state== _SPTHREAD_STATE_INITIALIZED ) {
         goto found_ctl_struct;
      }
   }
   // apparently no control structures are available
   return EAGAIN;

   found_ctl_struct:

   _spthread_ctl_array[ii].state= _SPTHREAD_STATE_RUNNING;
   if ( attr_ptr == NULL ) {
      _spthread_set_attr_to_defaults( &(_spthread_ctl_array[ii]->attrs) );
   } else {
      _spthread_ctl_array[ii].attrs= *attr_ptr;
   }
   *thread_ptr= &_spthread_ctl_array[ii];
   /* TODO: refine the thread start code here */ 
   //;;__SMACK_code( "call {:async} spthread_ftn_wrapper( " 
   //;;	 "thread_ptr, start_routine_ptr, arg_ptr );" ); 
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
#endif /* !defined(__SPTHREAD_H__) */

