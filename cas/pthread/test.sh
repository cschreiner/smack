#!/bin/bash
# run a standard test suite on the spthread library.

function test_one_program()
{
   arg_program="$1"
   arg_expected_result="$2"
   echo "running \"$arg_program\", expecting \"$expected_result\"".

   ./smack_for_pthreads "$1" | grep -v -e "^Boogie verification time:" \
         -e "^Time spent reading-writing programs: .* s" \
         -e "^Time spent checking a program .* s" \
         -e "^Time spent checking a path .* s" \
         -e "^Number of procedures inlined: " \
         -e "^Number of variables tracked: " \
         -e "^Total Time: .* s" \
         -e "^ *$" | \
      grep -q ^
   status=$?

   if [ "$arg_expected_result" = "ok" ]; then
      if [ $status -eq 1 ]; then
	 echo "  " \"$arg_program\" corrrectly found no bugs. 
      else 
	 echo "  " \"$arg_program\" incorrrectly found bugs. 
      fi
   elif [ "$arg_expected_result" = "bug" ]; then
      if [ $status -eq 0 ]; then
	 echo "  " \"$arg_program\" corrrectly found bugs. 
      else 
	 echo "  " \"$arg_program\" incorrrectly found no bugs. 
      fi
   fi

   return 0
}

test_one_program test1/test_all_spthread.c ok
test_one_program test1/test_z.c ok
test_one_program test1/test_z_w_error.c bug

test_one_program test_storm/account_pthread.c ok
test_one_program test_storm/account_pthread_w_error2.c bug
test_one_program test_storm/account_pthread_w_error.c bug

# end of script



