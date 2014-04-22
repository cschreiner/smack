/* test to see if SMACK is being defined as I understand it should.
*/
#include "/uusoc/scratch/euler/cas/tuut/x86_64/smack-project/smack/install/include/smack/smack.h"

int printf_stub( char* st );

#if defined(SMACK)
   #error "SMACK is defined"
#elif defined(_SMACK)
   #error "_SMACK is defined"
#elif defined(__SMACK)
   #error "__SMACK is defined"
#elif defined(_SMACK_)
   #error "_SMACK_ is defined"
#elif defined(__SMACK__)
   #error "__SMACK__ is defined"
#else
   #error "neither SMACK nor its variants are defined"
#endif

#error "Verified that preprocessor errors work."

int main( int argc, char* argv[] )
{{
   printf_stub( "Hello, world. \n" );
}}

