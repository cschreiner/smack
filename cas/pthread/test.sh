#!/bin/sh
# run a standard test suite on the spthread library.

./smack_for_pthreads test1/test_all_spthread.c
./smack_for_pthreads test1/test_z.c
./smack_for_pthreads test1/test_z_w_error.c

./smack_for_pthreads test_storm/account_pthread.c
./smack_for_pthreads test_storm/account_pthread_w_error2.c
./smack_for_pthreads test_storm/account_pthread_w_error.c




