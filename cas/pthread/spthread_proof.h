/*** 
   * Program Name: SMACK spthreads
   *
   * File Name: spthread_proof.h
   *
   * File Description: proof macros for spthreads
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

#if !defined(__SPTHREAD_PROOF_H__)
#define __SPTHREAD_PROOF_H__

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
#if defined(_SPTHREAD_FAULT_TOLERANT_PROOFS)
   #define _spthread_state_valid_assumption( aa )
#else
   #define _spthread_state_valid_assumption( aa ) \
      __SMACK_assume( "(_SPTHREAD_STATE_FIRST < (" #aa ") ) && " \
	    "( (" #aa ") < _SPTHREAD_STATE_LAST" );
#endif


#if defined(_SPTHREAD_FAULT_TOLERANT_PROOFS)
   #define _spthread_mutex_type_valid_assumption(aa) /* intentionally nothing */
#else
   #define _spthread_mutex_type_valid_assumption(aa)  \
      __SMACK_assume( "(_SPTHREAD_MUTEX_TYPE_FIRST < (" #aa ") ) && " \
	    "( (" #aa ") < _SPTHREAD_MUTEX_TYPE_LAST )" );
#endif

#if defined(_SPTHREAD_FAULT_TOLERANT_PROOFS)
   #define _spthread_mutex_lock_valid_assumption(aa) /* intentionally nothing */
#else
   #define _spthread_mutex_lock_valid_assumption(aa)  \
      __SMACK_assume( "(_SPTHREAD_MUTEX_FIRST < (" #aa ") ) && " \
	    "( (" #aa ") < _SPTHREAD_MUTEX_LAST )" );
#endif


/*** ==========================================================================
   *   proofs related to function prototypes and line functions
   */

/* for spthread_create() */
#define _spthread_ctl_array_bounds_ptr_thm( aa ) \
      __SMACK_assert( "(&_spthread_ctl_arry[0] <= (" #aa ") ) && " \
	 "( (" #aa ") <= _spthread_ctl_arry[_SPTHRAD_MAX_THREADS] )" );
#define _spthread_ctl_array_bounds_idx_thm( aa )  \
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
#endif /* !defined(__SPTHREAD_PROOF_H__) */

