/*** 
   * Program Name: SMACK spthreads
   *
   * File Name: spthread_mutex.h
   *
   * File Description: mutex locking structures for spthreads
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

#if !defined(__SPTHREAD_MUTEX_H__)
#define __SPTHREAD_MUTEX_H__

/*** **************************************************************************
   *   includes
   * **************************************************************************
   */
#include <stdlib.h>
#include <errno.h>

#include "/uusoc/scratch/euler/cas/edu/uut/smack/cas/pthread/spthread_proof.h"


/*** **************************************************************************
   *   declarations
   * **************************************************************************
   */
typedef enum { _SPTHREAD_MUTEX_TYPE_FIRST= 0x6B46, // random val 1...32768
      _SPTHREAD_MUTEX_TYPE_FAST,
      _SPTHREAD_MUTEX_TYPE_RECURSIVE,
      _SPTHREAD_MUTEX_TYPE_ERRORCHECK,
      _SPTHREAD_MUTEX_TYPE_LAST } _spthread_mutex_type_t;

#if defined(_SPTHREAD_FAULT_TOLERANT_PROOFS)
   #define _spthread_mutex_type_valid_assumption(aa) /* intentionally nothing */
#else
   #define _spthread_mutex_type_valid_assumption(aa)  \
      __SMACK_assume( "(_SPTHREAD_MUTEX_TYPE_FIRST < (" #aa ") ) && " \
	    "( (" #aa ") < _SPTHREAD_MUTEX_TYPE_LAST )" );
#endif

typedef struct {
   /* give this structure a dummy field until something is needed. */
   _spthread_mutex_type_t type;
} spthread_mutex_attr_t;
spthread_mutex_attr_t SPTHREAD_MUTEX_INITIALIZER= { _SPTHREAD_MUTEX_TYPE_FAST };
spthread_mutex_attr_t SPTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP= 
      { _SPTHREAD_MUTEX_TYPE_RECURSIVE };
spthread_mutex_attr_t SPTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP= 
      { _SPTHREAD_MUTEX_TYPE_ERRORCHECK };

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
   *   attr_ptr: a structure of attributes to set
   * 
   * Outputs: none
   *
   * Return Value: always returns 0
   *
   * TODO2: add support for RECURSIVE and ERRORCHECK mutexes. 
   */
int spthread_mutex_init( spthread_mutex_t* mutex_ptr, 
      const spthread_mutex_attr_t* attr_ptr )
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

   __SMACK_top_decl( "procedure corral_atomic_begin();" );
   __SMACK_top_decl( "procedure corral_atomic_end();" );

   __SMACK_code( "call corral_atomic_begin();" );

   // this statement derived from an algorithm by Zvonimir:
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

   __SMACK_top_decl( "procedure corral_atomic_begin();" );
   __SMACK_top_decl( "procedure corral_atomic_end();" );

   __SMACK_code( "call corral_atomic_begin();" );

   // this statement derived from an algorithm by Zvonimir:
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
#endif /* !defined(__SPTHREAD_MUTEX_H__) */

