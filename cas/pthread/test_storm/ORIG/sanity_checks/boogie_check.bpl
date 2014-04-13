

procedure main()
{
var x:int;

start:
x := 2;
goto label1;

label1:
goto label2;

label2:
assert x == 2;
return;
}

