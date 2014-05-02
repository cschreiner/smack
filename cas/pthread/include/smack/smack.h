#ifndef SMACK_H_
#define SMACK_H_

#include <stdbool.h>

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

/* templatle is 17 lines long */
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

#endif /*SMACK_H_*/
