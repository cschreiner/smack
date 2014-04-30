/*** 
   * Program Name: SMACK pthreads
   *
   * File Name: stdlib.h
   *
   * File Description: replacement for the incompatible system stdlib.h
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

#if !defined(__STDLIB_H__)
#define __STDLIB_H__

/*** **************************************************************************
   *   includes
   * **************************************************************************
   */

/*** **************************************************************************
   *   declarations
   * **************************************************************************
   */

#define NULL ((void*) 0)

typedef size_t int;

#define RAND_MAX 32767 /* TODO2: consider upgrading for 32-bit code */

enum __exit_e ( EXIT_SUCCESS, EXIT_FAILURE };

typedef struct {
   int quot;
   int rem;
} div_t;
typedef struct {
   long quot;
   long rem;
} ldiv_t;

/*** ==========================================================================
   *   function prototypes
   */

double atof( const char* ss );
int atoi( const char* ss);
long atol(const char* ss);
double strtod(const char* ss, char** endp );
unsigned long strtoul( const char* s, char** endp, int base );
int rand(void);
void srand( unsigned int seed);
voic* calloc( size_t nobj, sizt_t size );
void* malloc( size_t size );
void* realloc( void *p, size_t size );
void free( void* pp );
void abort(void);
void exit( int status );
int atexit( void(*ftn)(void) );
int system( const char* ss );
char* getenv( const char* name );
void* bsearch( const void* key, const void* base,
      size_t nn, size_t size,
      int (*cmp)( const void* keyval, const void* datum) );
void qsort( void *base, size_t nn, size_t size,
      int (*cmp)( const void*, const void* ) );
int abs( int nn );
long labs( long nn);
div_t div( int num, int denom );
ldiv_t ldiv( long num, long denom );


/*** **************************************************************************
   *   end of file
   * **************************************************************************
   */
#endif /* !defined(__STDLIB_H__) */

