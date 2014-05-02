/*** 
   * Program Name: SMACK pthreads
   *
   * File Name: smack_svcomp.h
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
   * $Source: /home/cas/templates/auto_uut/RCS/cas_tmpl.h,v $
   * $Author: cas $
   * $Date: 2014/05/02 19:51:11 $
   * $Revision: 1.4 $
   * 
   */

#if !defined(__SMACK_SVCOMP_H__)
#define __SMACK_SVCOMP_H__

/*** **************************************************************************
   *   includes
   * **************************************************************************
   */
#include <smack.h>

/*** **************************************************************************
   *   declarations
   * **************************************************************************
   */

/*** ==========================================================================
   *   function prototypes
   */

/*** --------------------------------------------------------------------------
   * macro __VERIFIER_assume()
   * --------------------------------------------------------------------------
   * Description: alias for __SMACK_assume()
   */
#define __VERIFIER_assume(xx) __SMACK_assume(xx)

/*** --------------------------------------------------------------------------
   * macro __VERIFIER_nondet_X()
   * --------------------------------------------------------------------------
   * Description: alias for __SMACK_nondet_X
   */
#define __VERIFIER_nondet_bool(xx) __SMACK_nondet_bool(xx)
#define __VERIFIER_nondet_char(xx) __SMACK_nondet_char(xx)
#define __VERIFIER_nondet_int(xx) __SMACK_nondet_int(xx)
#define __VERIFIER_nondet_float(xx) __SMACK_nondet_float(xx)
#define __VERIFIER_nondet_loff_t(xx) __SMACK_nondet_loff_t(xx)
#define __VERIFIER_nondet_long(xx) __SMACK_nondet_long(xx)
#define __VERIFIER_nondet_pchar(xx) __SMACK_nondet_pchar(xx)
#define __VERIFIER_nondet_pointer(xx) __SMACK_nondet_pointer(xx)
#define __VERIFIER_nondet_pthread_t(xx) __SMACK_nondet_pthread_t(xx)
#define __VERIFIER_nondet_sector_t(xx) __SMACK_nondet_sector_t(xx)
#define __VERIFIER_nondet_short(xx) __SMACK_nondet_short(xx)
#define __VERIFIER_nondet_size_t(xx) __SMACK_nondet_size_t(xx)
#define __VERIFIER_nondet_u32(xx) __SMACK_nondet_u32(xx)
#define __VERIFIER_nondet_uchar(xx) __SMACK_nondet_uchar(xx)
#define __VERIFIER_nondet_uint(xx) __SMACK_nondet_uint(xx)
#define __VERIFIER_nondet_ulong(xx) __SMACK_nondet_ulong(xx)
#define __VERIFIER_nondet_unsigned(xx) __SMACK_nondet_unsigned(xx)
#define __VERIFIER_nondet_ushort(xx) __SMACK_nondet_ushort(xx)
// template:
//#define __VERIFIER_nondet_X(xx) __SMACK_nondet_X(xx)

/*** --------------------------------------------------------------------------
   * macro __VERIFIER_atomic_begin()
   * macro __VERIFIER_atomic_end()
   * --------------------------------------------------------------------------
   * Description: alias for __SMACK_atomic_begin() and __SMACK_atomic_end()
   */
#define __VERIFIER_atomic_begin(xx) __SMACK_INIT();; __SMACK_atomic_begin(xx)
#define __VERIFIER_atomic_end(xx) __SMACK_INIT();; __SMACK_atomic_end(xx)


// template is 17 lines long
/*** --------------------------------------------------------------------------
   * function name()
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
//void name()


/*** **************************************************************************
   *   end of file
   * **************************************************************************
   */
#endif /* !defined(__SMACK_SVCOMP_H__) */

