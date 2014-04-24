#!/bin/bash
# run a standard test suite on the spthread library.

function test_one_program()
{
   arg_program="$1"
   arg_expected_result="$2"
   echo "running \"$arg_program\", expecting \"$arg_expected_result\"".

   # was:
   #./smack_for_pthreads "$1" | \
   bin/smack-verify-cas --verifier corral --mem-impls "$1" | \
      grep -v -e "^Boogie verification time:" \
         -e "^Time spent reading-writing programs: .* s" \
         -e "^Time spent checking a program .* s" \
         -e "^Time spent checking a path .* s" \
         -e "^Number of procedures inlined: " \
         -e "^Number of variables tracked: " \
         -e "^Total Time: .* s" \
         -e "^ *$" | \
      grep -qi ':.*fail' 
   status=$?

   if [ "$arg_expected_result" = "ok" ]; then
      if [ $status -eq 1 ]; then
	 echo "  " corrrectly found no bugs. 
      else 
	 echo "  " OOPS.  Incorrrectly found bugs. 
      fi
   elif [ "$arg_expected_result" = "bug" ]; then
      if [ $status -eq 0 ]; then
	 echo "  " corrrectly found bugs. 
      else 
	 echo "  " OOPS.  Incorrrectly found no bugs. 
      fi
   else
      echo ERROR: do not understand expected output \"$arg_expected_result\".
      exit -1
   fi

   return 0
}

test_one_program test1/test_all_spthread.c ok
test_one_program test1/test_all_spthread_w_error.c bug
test_one_program test1/test_z.c ok
test_one_program test1/test_z_w_error.c bug

test_one_program test_storm/account_pthread.c ok
test_one_program test_storm/account_pthread_w_error2.c bug
test_one_program test_storm/account_pthread_w_error.c bug

# end of script



