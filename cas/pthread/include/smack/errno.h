/*** 
   * Program Name: SMACK pthreads
   *
   * File Name: errno.h
   *
   * File Description: replacement with the smack-incompatible system * errno.h
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
   * $Date: 2014/04/04 10:34:34 $
   * $Revision: 1.3 $
   * 
   */

#if !defined(__ERRNO_H__)
#define __ERRNO_H__

/*** **************************************************************************
   *   includes
   * **************************************************************************
   */

/*** **************************************************************************
   *   declarations
   * **************************************************************************
   */

/* TODO2: this needs to be redefined on a per-thread basis.  This is usually
 * done as a macro.
 */
int errno;

/* define the various error values */
enum errno_e {
   ERRNO_CONST_FIRST= 20509, /* number chosen at random */
   EAGAIN, EINVAL, EPERM, EDEADLK, ESRCH,
   /* add more codes here as needed */
   ERRNO_CONST_LAST
};

/*** ==========================================================================
   *   function prototypes
   */

/*** **************************************************************************
   *   end of file
   * **************************************************************************
   */
#endif /* !defined(__ERRNO_H__) */

