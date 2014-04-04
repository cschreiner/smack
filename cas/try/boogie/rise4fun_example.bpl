/*
  Maximum in an array.
  
  This example illustrated finding specification and implementation errors
in Boogie programs,
  in presence of partial specifications (note that the loop invariant is
missing).
  Run "boogaloo test -p Max ArrayMax.bpl" to find bugs.
  
  Injected errors:
  - Precondition N > 0 is missing.
  - Initializing max with 0 is wrong when all elements of a are negative.
*/

// Iteratively compute the maximum element of the array a[0..N)
procedure Max(a: [int]int, N: int) returns (max: int)
  ensures (forall j: int :: 0 <= j && j < N ==> a[j] <= max);
  ensures (exists j: int :: 0 <= j && j < N && a[j] == max);
{
  var i: int;
  i := 0;
  max := 0;
  while (i < N) 
  {
    if (a[i] > max) {
      max := a[i];
    }
    i := i + 1;
  }
}

// Inputs to Max
const N: int;
const a: [int]int;

// One way to call Max
procedure Main() returns (max: int)
{
  assume N == 4;
  assume a[0] == 0 && a[1] == 10 && a[2] == 100 && a[3] == 5;
  call max := Max(a, N);
}


// Info: the 'arg:' line is used to send arguments to the tool.
// Hint: Use "test" for test mode and "-p PROC" to specify the procedure
// under test.
// arg: test -p Max
