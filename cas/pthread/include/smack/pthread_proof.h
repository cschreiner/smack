/*** 
   * Program Name: SMACK pthreads
   *
   * File Name: pthread_proof.h
   *
   * File Description: proof macros for pthreads
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

#if !defined(__PTHREAD_PROOF_H__)
#define __PTHREAD_PROOF_H__

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
#if defined(_PTHREAD_FAULT_TOLERANT_PROOFS)
   #define _pthread_state_valid_assumption( aa )
#else
   #define _pthread_state_valid_assumption( aa ) \
      __SMACK_assume( "(_PTHREAD_STATE_FIRST < (" #aa ") ) && " \
	    "( (" #aa ") < _PTHREAD_STATE_LAST" );
#endif


#if defined(_PTHREAD_FAULT_TOLERANT_PROOFS)
   #define _pthread_mutex_type_valid_assumption(aa) /* intentionally nothing */
#else
   #define _pthread_mutex_type_valid_assumption(aa)  \
      __SMACK_assume( "(_PTHREAD_MUTEX_TYPE_FIRST < (" #aa ") ) && " \
	    "( (" #aa ") < _PTHREAD_MUTEX_TYPE_LAST )" );
#endif

#if defined(_PTHREAD_FAULT_TOLERANT_PROOFS)
   #define _pthread_mutex_lock_valid_assumption(aa) /* intentionally nothing */
#else
   #define _pthread_mutex_lock_valid_assumption(aa)  \
      __SMACK_assume( "(_PTHREAD_MUTEX_FIRST < (" #aa ") ) && " \
	    "( (" #aa ") < _PTHREAD_MUTEX_LAST )" );
#endif


/*** ==========================================================================
   *   proofs related to function prototypes and line functions
   */

/* for pthread_create() */
#define _pthread_ctl_array_bounds_ptr_thm( aa ) \
      __SMACK_assert( "(&_pthread_ctl_arry[0] <= (" #aa ") ) && " \
	 "( (" #aa ") <= _pthread_ctl_arry[_SPTHRAD_MAX_THREADS] )" );
#define _pthread_ctl_array_bounds_idx_thm( aa )  \
      __SMACK_assert( "(0 <= (" #aa ") ) && " \
	 "( (" #aa ") ) <= _SPTHRAD_MAX_THREADS " );



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
#endif /* !defined(__PTHREAD_PROOF_H__) */

