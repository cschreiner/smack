/*** 
   * Program Name: SMACK pthreads
   *
   * File Name: stdbool.h
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
   * $Date: 2014/04/04 10:34:34 $
   * $Revision: 1.3 $
   * 
   */

#if !defined(__STDBOOL_H__)
#define __STDBOOL_H__

/*** **************************************************************************
   *   includes
   * **************************************************************************
   */

/*** **************************************************************************
   *   declarations
   * **************************************************************************
   */

typedef unsigned char _Bool;
#define bool _Bool
#define true 1
#define false 0

#define _bool_true_false_are_defined 1

/*** ==========================================================================
   *   function prototypes
   */

/*** **************************************************************************
   *   end of file
   * **************************************************************************
   */
#endif /* !defined(__STDBOOL_H__) */

