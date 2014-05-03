#ifndef SMACK_H_
#define SMACK_H_

#include <stdbool.h>
#include <stdlib.h>

void __SMACK_code(const char *fmt, ...);
void __SMACK_mod(const char *fmt, ...);
void __SMACK_decl(const char *fmt, ...);
void __SMACK_top_decl(const char *fmt, ...);

void __SMACK_assert(bool v) {
  __SMACK_code("assert {@} != 0;", v);
}

void __SMACK_assume(bool v) {
  __SMACK_code("assume {@} != 0;", v);
}

//// PROBLEM: in the 2D memory model, the declaration of boogie_si_record_int
//// should have a type $ptr parameter, not an int.  How should we do this?
// void __SMACK_record_int(int i) {
//   __SMACK_top_decl("procedure boogie_si_record_int(i:int);");
//   __SMACK_code("call boogie_si_record_int(@);", i);
// }

/*** **************************************************************************
   *   type definitions ideally defined by our C compiler 
   * **************************************************************************
   */
/* per definitions in some SV Comp '14 code */
typedef unsigned long sector_t;

/* per http://cboard.cprogramming.com/cplusplus-programming/97972-how-convert-string-into-pchar.html */
typedef char* pchar;

/* per definitions in some SV Comp '14 code */
typedef unsigned int u32;

/* per definitions in some SV Comp '14 code */
typedef long long loff_t;

/*** **************************************************************************
   *   function prototypes & macros
   * **************************************************************************
   */

/*** --------------------------------------------------------------------------
   * function __SMACK_nondet()
   * --------------------------------------------------------------------------
   * Description: returns a non-deterministic value. This is sometimes 
   *	useful to help verify that a property holds for any legal value. 
   *
   * Method:
   *
   * Reentrancy:
   *
   * Inputs: none
   * 
   * Outputs: none
   *
   * Return Value: a non-deterministic integer value.  If a subset of the
   *	integers is desired, follow the call to this function with an
   *	__SMACK_assume() statement defining the restriction.  For example:
   *
   *	xx= __SMACK_nondet();
   *	__SMACK_assume( 0 <= xx && xx < 100 );
   */
int __SMACK_nondet() {
  static int XXX;
  int x = XXX;
  __SMACK_code("havoc @;", x);
  return x;
}

/*** --------------------------------------------------------------------------
   * macro __SMACK_INIT()
   * --------------------------------------------------------------------------
   * Description: Must be called at the top of a function making certain 
   *	Smack API functions.  This macro inserts __SMACK_top_decl() calls 
   *	needed by those functions.
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
#define __SMACK_INIT() \
   __SMACK_top_decl( "procedure corral_atomic_begin();" );  \
   __SMACK_top_decl( "procedure corral_atomic_end();" ); 


/*** --------------------------------------------------------------------------
   * macro __SMACK_atomic_begin()
   * macro __SMACK_atomic_end()
   * --------------------------------------------------------------------------
   * Description: begins (ends) an block of atomic code i.e. code that may
   *	not be interrupted by task swaps.
   *
   *    A non-deterministic value is sometimes useful to help verify that a
   *    property holds for any legal value.
   *
   * Method: 
   *
   * Reentrancy: yes, these are safe to use in a reentrant environment.
   *
   * Inputs: none
   * 
   * Outputs: none
   *
   * Return Value: void
   *
   */
#define __SMACK_atomic_begin() __SMACK_code( "call corral_atomic_begin();" )
#define __SMACK_atomic_end() __SMACK_code( "call corral_atomic_end();" )

/*** --------------------------------------------------------------------------
   * function __SMACK_nondet_X()
   * --------------------------------------------------------------------------
   * Description: returns a nondeterministic value of type X.  
   *	Supported types are:
   *	bool, char, int, float, loff_t, long, pchar, pointer, pthread_t, 
   *	sector_t, short, size_t, u32, uchar, uint, ulong, unsigned, ushort.
   *
   * Method: 
   *
   * Reentrancy: 
   *
   * Inputs: none
   * 
   * Outputs: none
   *
   * Return Value: a non-deterministic value of the type X.
   *
   */
// template is 7 lines long:
//X __SMACK_nondet_X()
//{{
//  static X AAA;
//  X zz = AAA;
//  __SMACK_code("havoc @;", zz);
//  return zz;
//}}
int __SMACK_nondet_bool()
{{
  static bool AAA;
  bool zz = AAA;
  __SMACK_code("havoc @;", zz);
  __SMACK_assume( (zz==0) || (zz==1) );
  return zz;
}}
char __SMACK_nondet_char()
{{
  static char AAA;
  char zz = AAA;
  __SMACK_code("havoc @;", zz);
  return zz;
}}
int __SMACK_nondet_int()
{{
  static int AAA;
  int zz = AAA;
  __SMACK_code("havoc @;", zz);
  return zz;
}}
// Why does this cause a smack to emit a weird error message?
//;; float __SMACK_nondet_float()
//;; {{
//;;   static float AAA;
//;;   float zz = AAA;
//;;   __SMACK_code("havoc @;", zz);
//;;   return zz;
//;; }}
loff_t __SMACK_nondet_loff_t()
{{
  static loff_t AAA;
  loff_t zz = AAA;
  __SMACK_code("havoc @;", zz);
  return zz;
}}
long __SMACK_nondet_long()
{{
  static long AAA;
  long zz = AAA;
  __SMACK_code("havoc @;", zz);
  return zz;
}}
pchar __SMACK_nondet_pchar()
{{
  static pchar AAA;
  pchar zz = AAA;
  __SMACK_code("havoc @;", zz);
  return zz;
}}
void* __SMACK_nondet_pointer()
{{
  static void* AAA;
  void* zz = AAA;
  __SMACK_code("havoc @;", zz);
  return zz;
}}
sector_t __SMACK_nondet_sector_t()
{{
  static sector_t AAA;
  sector_t zz = AAA;
  __SMACK_code("havoc @;", zz);
  return zz;
}}
short __SMACK_nondet_short()
{{
  static short AAA;
  short zz = AAA;
  __SMACK_code("havoc @;", zz);
  return zz;
}}
size_t __SMACK_nondet_size_t()
{{
  static size_t AAA;
  size_t zz = AAA;
  __SMACK_code("havoc @;", zz);
  return zz;
}}
u32 __SMACK_nondet_u32()
{{
  static u32 AAA;
  u32 zz = AAA;
  __SMACK_code("havoc @;", zz);
  return zz;
}}
unsigned char __SMACK_nondet_uchar()
{{
  static unsigned char AAA;
  unsigned char zz = AAA;
  __SMACK_code("havoc @;", zz);
  return zz;
}}
unsigned int __SMACK_nondet_uint()
{{
  static unsigned int AAA;
  unsigned int zz = AAA;
  __SMACK_code("havoc @;", zz);
  return zz;
}}
unsigned long __SMACK_nondet_ulong()
{{
  static unsigned long AAA;
  unsigned long zz = AAA;
  __SMACK_code("havoc @;", zz);
  return zz;
}}
unsigned __SMACK_nondet_unsigned()
{{
  static unsigned AAA;
  unsigned zz = AAA;
  __SMACK_code("havoc @;", zz);
  return zz;
}}
unsigned short __SMACK_nondet_ushort()
{{
  static unsigned short AAA;
  unsigned short zz = AAA;
  __SMACK_code("havoc @;", zz);
  return zz;
}}


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

/* template is 17 lines long */
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

#endif /*SMACK_H_*/
