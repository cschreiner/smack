/* test to see if SMACK is being defined as I understand it should.
*/
#include "/uusoc/scratch/euler/cas/tuut/x86_64/smack-project/smack/install/include/smack/smack.h"

int printf_stub( char* st );


#ifdef SMACK
   #error "SMACK is defined"
#else
   #error "SMACK is not defined"
#endif

#error "silly message"

int main( int argc, char* argv[] )
{{
   printf_stub( "Hello, world. \n" );
}}

