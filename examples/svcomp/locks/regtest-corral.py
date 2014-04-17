#! /usr/bin/env python

import subprocess
import re
import time

# list of regression tests with the expected outputs
tests = [
  ('test_locks_5_true',     r'Program has no bugs'),
  ('test_locks_6_true',     r'Program has no bugs'),
  ('test_locks_7_true',     r'Program has no bugs'),
  ('test_locks_8_true',     r'Program has no bugs'),
  ('test_locks_9_true',     r'Program has no bugs'),
  ('test_locks_10_true',    r'Program has no bugs'),
  ('test_locks_11_true',    r'Program has no bugs'),
  ('test_locks_12_true',    r'Program has no bugs'),
  ('test_locks_13_true',    r'Program has no bugs'),
  ('test_locks_14_true',    r'Program has no bugs'),
  ('test_locks_14_false',   r'This assertion can fail'),
  ('test_locks_15_true',    r'Program has no bugs'),
  ('test_locks_15_false',   r'This assertion can fail')
]

def red(text):
  return '\033[0;31m' + text + '\033[0m'
  
def green(text):
  return '\033[0;32m' + text + '\033[0m'

def runtests():
  passed = failed = 0
  for test in tests:
    
    for mem in ['flat']:
    
      print "{0:>20} {1:>8}:".format(test[0], "(" + mem + ")"),

      # invoke SMACK
      t0 = time.time()
      p = subprocess.Popen(['smack-verify.py', test[0] + '.bc', '--verifier=corral',
                            '--mem-mod=' + mem, '-o', test[0] +'.bpl'],
                            stdout=subprocess.PIPE)
      
      smackOutput = p.communicate()[0]
      elapsed = time.time() - t0

      # check SMACK output
      if re.search(test[1], smackOutput):
        print green('PASSED') + '  [%.2fs]' % round(elapsed, 2)
        passed += 1
      else:
        print red('FAILED')
        failed += 1
  
  return passed, failed

if __name__ == '__main__':

  passed, failed = runtests()
  
  print '\nPASSED count: ', passed
  print 'FAILED count: ', failed

