/*** 
   * Program Name: SMACK pthreads
   *
   * File Name: stdio.h
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

#if !defined(__STDIO_H__)
#define __STDIO_H__

/*** **************************************************************************
   *   includes
   * **************************************************************************
   */
#include <stdlib.h>

/*** **************************************************************************
   *   declarations
   * **************************************************************************
   */

typedef struct {
   char dummy;
} FILE;
FILE* stdin; 
FILE* stdout; 
FILE* stderr; 

const int EOF= 0;
const size_t L_tmpnam= 32767; // TODO2: consider shortening this
const size_t TMP_MAX= 1024;
const size_t BUFSIZ= 32767; // TODO2: consider adjusting this
const int _IOFBF= 30003;
const int _IOLBF= 30004;
const int _IONBF= 30005;

const int SEEK_SET= 28290;
const int SEEK_CUR= 28291;
const int SEEK_END= 28292;

typedef size_t fpos_t;

/*** ==========================================================================
   *   function prototypes
   */

FILE* fopen( const char* filename, const char* mode );
FILE* freopen( const char* filename, const char* mode, FILE* stream );
int fflush( FILE* stream );
int fclose( FILE* stream );
int remove( const char* filename );
int rename( const char* oldname, const char* newname );
FILE* tmpfile(void);
char* tmpnam( char s[L_tmpnam]);
int setvbuf( FILE* stream, char* buf, int mode, size_t size );
void stetbuf( FILE* stream, char* buf );
int fprintf( FILE* stream, const char* format, ... );
int printf( const char* format, ... );
int sprintf( char* ss, const char* format, ... );
int snprintf(char* str, size_t size, const char* format, ...);

#if 0 /* add when stdarg.h is available */
   vprintf( const char* format, va_list arg );
   vfprintf( FILE* stream, const char* format, va_list arg );
   vsprintf( char* ss, const char* format, va_list arg );
#endif

int fscanf( FILE* stream, const char* format, ... );
int scanf( const char* format, ... );
int sscanf( const char* ss, const char* format, ... );
int fgetc( FILE* stream );
char* fgets( char* ss, int nn, FILE* stream );
int fputc( int cc, FILE* stream );
int fputs( const char* ss, FILE* stream );
int getc( FILE* stream );
int getchar( void );
char* gets( char* ss );
int putc( int cc, FILE* stream );
int putchar( int cc )
{{
   return putc( cc, stdout );
}}
int puts( const char* ss );
int ungetc( int cc, FILE* stream );

size_t fread( void* ptr, size_t size, size_t nobj, FILE* stream );
size_t fwrite( const void* ptr, size_t size, size_t nobj, FILE* stream );
int fseek( FILE* stream, long offset, int origin );
long ftell( FILE* stream );
void rewind( FILE* stream );
int fgetpos( FILE* stream, fpos_t *ptr );
int fsetpos( FILE* stream, const fpos_t* ptr );


/*** **************************************************************************
   *   end of file
   * **************************************************************************
   */
#endif /* !defined(__STDIO_H__) */

