/* test to see if SMACK is being defined as I understand it should.
*/
#include <stdio.h>
#include "/uusoc/scratch/euler/cas/tuut/x86_64/smack-project/smack/install/include/smack/smack.h"

#ifdef SMACK
   #error SMACK is defined
#endif

int main( int argc, char* argv[] )
{{
   printf( "Hello, world. \n" );
}}

