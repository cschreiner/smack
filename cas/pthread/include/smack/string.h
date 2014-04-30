/*** 
   * Program Name: SMACK pthreads
   *
   * File Name: string.h
   *
   * File Description: replacement for the ill-suited system file
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

#if !defined(__STRING_H__)
#define __STRING_H__

/*** **************************************************************************
   *   includes
   * **************************************************************************
   */
#include <stdlib.h>

/*** **************************************************************************
   *   declarations
   * **************************************************************************
   */

/*** ==========================================================================
   *   function prototypes
   */

char* strcpy( char* dest, const char* src );
char *strncpy( char* dest, const char* src, size_t len );
char* strct( char* dest, const char* src );
char* strnct( char* dest, const char* src, size_t len );
int strcmp( const char* aa, const char* bb );
int strncmp( const char* aa, const char* bb, size_t len );
char* strchr( const char* st, int c );
char* strrchr( const char* st, int c );
size_t strspn( const char* aa, const char* bb );
size_t strcspn( const char* aa, const char* bb );
char* strpbrk( const char* aa, const char* bb );
char* strstr( const char* aa, const char* bb );
size_t strlen( const char *st );
char* strerror( int nn );
char* strtok( char* st, const char* aa );

void* memcpy( void* dest, const void* src, size_t len );
void* memmove( void* dest, const void* src, size_t len );
int memcmp( const void* aa, const void* bb, size_t len );
void* memchr( const void* st, int cc, size_t len );
void* memset( void* dest, int cc, size_t len );


/*** **************************************************************************
   *   end of file
   * **************************************************************************
   */
#endif /* !defined(__STRING_H__) */

