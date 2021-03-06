#! /usr/bin/env python

from os import path
import sys
import re
import argparse
import platform
from llvm2bpl import *

VERSION = '1.4.0'


def smackParser():
  parser = argparse.ArgumentParser(add_help=False, parents=[llvm2bplParser()])
  parser.add_argument('--verifier', dest='verifier',
                      choices=['boogie-plain', 'boogie-inline', 'corral'],
                      default='boogie-inline',
                      help='set the underlying verifier format')
  parser.add_argument('--entry-points', metavar='PROC', dest='entryPoints',
                      default='main', nargs='+',
                      help='specify entry procedures')
  return parser


def addInline(match, entryPoints):
  procName = match.group(1)
  procDef = ''
  if procName in entryPoints:
    procDef += 'procedure ' + procName + '('
  else:
    procDef += 'procedure {:inline 1} ' + procName + '('
  return procDef


def addEntryPoint(match, entryPoints):
  procName = match.group(1)
  procDef = ''
  if procName in entryPoints:
    procDef += 'procedure {:entrypoint} ' + procName + '('
  else:
    procDef += 'procedure ' + procName + '('
  return procDef


def clang(scriptPathName, inputFile):
  scriptFullPath = path.abspath(scriptPathName)
  smackRoot = path.dirname(scriptFullPath)
  smackHeaders = path.join(smackRoot, 'include', 'smack')

  fileName = path.splitext(inputFile.name)[0]

  print "smackHeader dir=\"" + smackHeaders+ "\"" #;;

  # original form, using -nostdinc to inhibit loading conflicting standard
  # header files:  
  #p = subprocess.Popen(['clang', '-c', '-Wall', '-emit-llvm', '-O0', '-g',
  #  '-I' + smackHeaders, inputFile.name, '-nostdinc', '-D__SMACK=', 
  #  '-o', fileName + '.bc'])
   
  # an alternate means:
  #p = subprocess.Popen(['clang', '-c', '-Wall', '-emit-llvm', '-O0', '-g',
  #  '-I' + smackHeaders, inputFile.name, '-fno-builtin', '-D__SMACK=', 
  #  '-o', fileName + '.bc'])
   
  # On 2014apr30, Zvonimir recommended this:
  p = subprocess.Popen(['clang', '-c', '-emit-llvm', '-O0', 
      '-I' + smackHeaders, inputFile.name, '-D__SMACK=', 

      # TODO: only insert these options iff an appropriate command-line
      #option was given to this script, like 'include <file>' or '--sv-comp'.
      '-include', 'smack_svcomp.h', #;;
      
      # This option suppresses the no-return-statement error messages from the
      # raw sv-comp task .c files that don't have return statements at the end
      # of functions.  Unfortunately, this also suppresses enough information
      # in the clang output that smack can't find an assertion failure.
      #'-Wno-return-type',
                        
      '-o', fileName + '.bc'])
  p.wait()

  if p.returncode != 0:
    sys.exit("SMACK encountered a clang error. Exiting...")

  inputFileName = path.join(path.curdir, fileName + '.bc')
  inputFile = open(inputFileName, 'r')
  return inputFile


def smackGenerate(scriptPathName, inputFile, debugFlag, memmod, memimpls,
                  verifier, entryPoints):
  fileExtension = path.splitext(inputFile.name)[1]
  if fileExtension == '.c':
    # if input file is .c, then compile it first with clang
    inputFile = clang(scriptPathName, inputFile)

  bpl = llvm2bpl(inputFile, debugFlag, memmod, memimpls)
  inputFile.close()

  p = re.compile('procedure\s+([^\s(]*)\s*\(')
  if verifier == 'boogie-inline':
    # put inline on procedures
    bpl = p.sub(lambda match: addInline(match, entryPoints), bpl)
  elif verifier == 'corral':
    # annotate entry points
    bpl = p.sub(lambda match: addEntryPoint(match, entryPoints), bpl)
  return bpl


if __name__ == '__main__':

  # parse command line arguments
  parser = argparse.ArgumentParser(
            description='Outputs the appropriately annotated Boogie file '+
                'generated from the input LLVM file.',
            parents=[smackParser()])
  args = parser.parse_args()

  bpl = smackGenerate(path.dirname(sys.argv[0]), args.infile, args.debug,
                      args.memmod, args.memimpls, args.verifier,
                      args.entryPoints)

  # write final output
  args.outfile.write(bpl)
  args.outfile.close()

