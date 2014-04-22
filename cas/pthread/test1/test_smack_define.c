/* test to see if SMACK is being defined as I understand it should.
*/
#include "/uusoc/scratch/euler/cas/tuut/x86_64/smack-project/smack/install/include/smack/smack.h"

#ifdef SMACK
   #error SMACK is defined
#endif

